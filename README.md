# Smart Library — OS Lab Assignment 1

A simple simulation of readers receiving service from librarians.

## Group Members

- Urvashi: process model and overall structure
- Aarush: FCFS scheduling
- Samar: Priority Scheduling
- Kabir: evaluation metrics and output

## Scenario

Scenario Chosen: Library

## Project constraints

- Each reader is a process with a unique ID, arrival time, priority, service time, and category.
- There are two identical librarians, so at most two readers can receive service at once.
- Implement FCFS and non-preemptive Priority Scheduling; a reader finishes service once started.
- FCFS uses arrival order, with equal arrivals ordered by lexicographic ID.
- Priority Scheduling uses the smaller numerical priority first, then earlier arrival, then lexicographic ID.
- Arrival times are non-negative integers; service times and priorities are positive integers.
- Use simulated time in a single-threaded program; memory management and concurrency are outside this assignment.
- Track arrival, waiting, execution, and completion, and report scheduling metrics for comparing the algorithms.
- Follow the PDF's input, command-line, and machine-readable output formats.

## Code files

- `src/main.cpp`: Reads the command-line arguments, loads readers, and calls the selected scheduler.
- `src/input.h`: Declares the input-reading function.
- `src/input.cpp`: Reads the reader records from a file and checks for an empty or unavailable file.
- `src/process.h`: Defines the shared process fields, reader categories, and process states.
- `src/fcfs.h`: Declares the FCFS function and defines its result structure.
- `src/fcfs.cpp`: Implements FCFS for two librarians and returns each reader's start and completion times.
- `src/priority.h`: Declares the Priority Scheduling function and its result structure.
- `src/priority.cpp`: Implements Priority Scheduling for two librarians and and returns each reader's start and completion times.
- `src/metrics.h`: Declares the per-reader and summary metric structures and functions.
- `src/metrics.cpp`: Computes waiting, turnaround, and response time per reader, and the averages, throughput, and utilization.
- `src/output.h`: Declares the machine-readable output function.
- `src/output.cpp`: Prints the result rows in lexicographic ID order, followed by the `SUMMARY` block.

The full assignment specification is in [docs/OSLab_CS_3710__A1_Specifications.pdf](docs/OSLab_CS_3710__A1_Specifications.pdf).

## Compile and run

```bash
g++ -std=c++17 src/*.cpp -o library
./library input.txt FCFS
./library input.txt PRIORITY
```

## Command-Line Arguments

```
./library INPUT_FILE ALGORITHM
```

- `INPUT_FILE`: path to an input file in the standardized format (Section 12 of the specification).
- `ALGORITHM`: `FCFS` or `PRIORITY` (uppercase). Any other value prints an error and exits with status 1.

The input file contains the number of readers N, the Round Robin quantum Q (read but not used, since Library has no Round Robin), and one `ID,ARRIVAL,PRIORITY,SERVICE,CATEGORY` record per line.

## Process Model

Each reader is one process (`src/process.h`) with:

- `pid`: unique reader ID, stored as a string so IDs can be compared lexicographically.
- `arrival_time`: when the reader enters the library and becomes eligible for service.
- `priority`: smaller number = higher priority.
- `service_time`: the simulated duration of the reader's service, the equivalent of a CPU burst.
- `category`: `REGULAR`, `FACULTY`, `RESEARCHER`, etc. It is descriptive only; scheduling uses the numerical priority.

The two librarians are two identical service units, so at most two readers are served at once.

The lifecycle NEW → READY → RUNNING → TERMINATED is modelled implicitly. A reader is NEW until its arrival time, READY while it has arrived but not started, RUNNING from its start time to its completion time, and TERMINATED afterwards. Since both algorithms are non-preemptive, a reader never goes from RUNNING back to READY.

## Scheduling Algorithms

Both algorithms are non-preemptive. Whenever a librarian becomes free, the scheduler picks one reader from those who have arrived, and that reader is served until finished. If nobody has arrived yet, the clock jumps to the next arrival, so idle periods are handled without waiting in real time.

### FCFS (`src/fcfs.cpp`)

Readers are sorted by arrival time, with equal arrivals ordered by lexicographic ID. Each reader in that order goes to the librarian who becomes free first, starting at whichever is later: the librarian's free time or the reader's arrival.

### Priority Scheduling (`src/priority.cpp`)

When a librarian becomes free, it serves the arrived reader with the smallest priority number. Ties go to the earlier arrival, then to the lexicographically smaller ID. A higher-priority reader who arrives during service waits for the next free librarian; nobody is interrupted.

## Design Decisions and Assumptions

- The simulation runs on simulated time, so the same input and algorithm always give the same output.
- Both librarians are identical. When both are free at the same moment, librarian 0 is used first. This does not change any reported metric.
- Scheduling and metrics are kept separate. The schedulers return only start and completion times, and `src/metrics.cpp` derives every metric from them.
- Process IDs are compared as strings, as the specification requires (so `R10` sorts before `R2`).
- Elapsed time: the specification does not say when "simulation elapsed time" E starts. We measure it from the first arrival to the last completion, the same window used for throughput. If the first reader arrives at time 0, this is identical to measuring from time 0.
- Busy time B is the sum of all service times, since a librarian is never interrupted.
- Input is assumed to be valid, as stated in Section 12.2 of the specification.

## Output

The program prints machine-readable output in the format from Section 15 of the specification:

```
PROCESS_ID,ARRIVAL,PRIORITY,SERVICE,START,COMPLETION,WAITING,TURNAROUND,RESPONSE
...
SUMMARY
AVERAGE_WAITING,...
AVERAGE_TURNAROUND,...
AVERAGE_RESPONSE,...
THROUGHPUT,...
UTILIZATION,...
```

Rows are sorted by lexicographic reader ID (so `R10` comes before `R2`). Summary values are printed with six decimal places.

## Metrics

For reader *i*, let A = arrival time, S = first start time, C = completion time, B = service time.

- **Completion time**: C, the time the reader's service ends.
- **Turnaround time**: TAT = C − A.
- **Waiting time**: WT = TAT − B. Both algorithms are non-preemptive, so this equals the response time.
- **Response time**: RT = S − A.
- **Throughput**: N / (last completion − first arrival), in readers per simulation time unit.
- **Utilization**: B_total / (M × E) × 100, where M = 2 librarians, B_total is the sum of all service times, and E = last completion − first arrival (see Design Decisions and Assumptions).

## Comparing Algorithms

On input.txt, the average waiting time is 8.05 under FCFS and 7.70 under PRIORITY. But priority-4 readers wait much longer under PRIORITY: R3 waits 25 vs 7 and R9 waits 24 vs 15.

All numbers below are actual output of `./library`.

### Summary results

| Input | Algorithm | Avg waiting | Avg turnaround | Avg response | Avg completion | Last completion | Throughput | Utilization (%) |
|---|---|---|---|---|---|---|---|---|
| `input.txt` (20 readers) | FCFS | 8.05 | 12.30 | 8.05 | 41.35 | 113 | 0.1770 | 37.61 |
| `input.txt` (20 readers) | PRIORITY | 7.70 | 11.95 | 7.70 | 41.00 | 112 | 0.1786 | 37.95 |
| `tests/inputs/spec_sample.txt` (5 readers) | FCFS | 2.60 | 7.60 | 2.60 | 9.60 | 13 | 0.3846 | 96.15 |
| `tests/inputs/spec_sample.txt` (5 readers) | PRIORITY | 2.20 | 7.20 | 2.20 | 9.20 | 13 | 0.3846 | 96.15 |
| `tests/inputs/starvation.txt` (8 readers) | FCFS | 1.375 | 5.00 | 1.375 | 8.88 | 16 | 0.5000 | 90.63 |
| `tests/inputs/starvation.txt` (8 readers) | PRIORITY | 2.125 | 5.75 | 2.125 | 9.63 | 16 | 0.5000 | 90.63 |

### Average waiting, turnaround and response time

On both `input.txt` and the specification sample, PRIORITY gives a lower average waiting and turnaround time than FCFS. Waiting time and response time are always equal here: both algorithms are non-preemptive, so a reader waits only once, before it starts. Turnaround time is waiting time plus the fixed service time, so it moves together with waiting time.

The overall average hides who benefits. Average waiting time on `input.txt` by priority level:

| Priority | Readers | FCFS | PRIORITY |
|---|---|---|---|
| 1 | 6 | 7.83 | 1.17 |
| 2 | 5 | 10.00 | 5.40 |
| 3 | 6 | 4.67 | 9.17 |
| 4 | 3 | 12.00 | 21.67 |

PRIORITY moves waiting time from priority 1–2 readers (faculty and researchers) onto priority 3–4 readers (regular readers). FCFS ignores priority completely, so a priority-1 reader such as R12 waits 17 time units behind earlier arrivals.

### Completion behaviour

Average completion time is almost the same (41.35 vs 41.00 on `input.txt`). Both algorithms are work-conserving: a librarian is never idle while a reader is waiting. So both finish the same total work at nearly the same time; what changes is mainly the order in which readers are served. The last completion differs by one unit (113 vs 112) because of the order in the late batch (R16–R20). FCFS serves R20 (service 6) last, starting at 107, while PRIORITY can start it at 106.

### Throughput and utilization

Total busy time (the sum of service times) is the same for both algorithms, so throughput and utilization differ only through the elapsed time E. On the spec sample and on `starvation.txt` they are identical. On `input.txt` PRIORITY is slightly higher only because it finishes one unit earlier. Utilization on `input.txt` is low (about 38%) for both because of the long idle period from t=36 (FCFS) or t=34 (PRIORITY) until t=100, when no readers are waiting. That idle time comes from the input, not from the scheduler.

### When the policies behave differently

The two algorithms give the same schedule when there is at most one waiting reader at each decision, for example in `single_reader.txt`, `long_idle.txt` and `identical_readers.txt`. They differ only when several readers are waiting at once:

- **Simultaneous arrivals** (`same_arrival.txt`): FCFS serves in ID order (R1, R2 first). PRIORITY serves R3 and R4 (priority 1) first, and R1 (priority 3) waits 5 instead of 0.
- **A high-priority reader arrives while both librarians are busy** (spec sample): when a librarian frees up at t=5, FCFS serves R3 because it arrived earlier, while PRIORITY serves R5 (priority 1). R5's wait drops from 6 to 1 and R3's rises from 3 to 6.
- **Equal priorities** (`equal_priority.txt`): PRIORITY falls back to arrival time and then ID, so it behaves exactly like FCFS.

### Starvation and fairness

PRIORITY has no aging, so a low-priority reader can starve. In `tests/inputs/starvation.txt`, regular reader R3 (priority 5, service 1) arrives at t=1, and faculty readers (priority 1) keep arriving every 2 time units:

- Under FCFS, R3 waits 3.
- Under PRIORITY, R3 waits 11. It is served only at t=12, once the faculty readers stop arriving.

R3's wait would grow without limit if the faculty arrivals never stopped. On `input.txt` the same effect gives the priority-4 readers R3 and R9 the two largest waits (25 and 24).

FCFS cannot starve anyone, since every reader is eventually at the front of the queue. It is fair by arrival order but ignores urgency, and a long service can hold up later readers (the convoy effect): in `long_and_short.txt`, R1's 1000-unit service occupies one librarian for the whole run.

In short, PRIORITY gives the best average and the best service to faculty and researchers. FCFS gives the most predictable, starvation-free service to everyone. A fix for PRIORITY's starvation would be aging, which this implementation does not include.

## Tests

`tests/inputs/` contains inputs for the Section 17 edge cases that apply to Library:

| File | Case |
|---|---|
| `spec_sample.txt` | Smart Library sample from the specification |
| `single_reader.txt` | Only one reader |
| `same_arrival.txt` | All readers arrive at the same time |
| `arrive_while_running.txt` | Readers arrive while both librarians are busy |
| `long_and_short.txt` | Very long and very short services |
| `equal_priority.txt` | Equal priorities (tie-break by arrival, then ID) |
| `equal_service.txt` | Equal service times |
| `identical_readers.txt` | Identical arrival, priority and service (tie-break by ID) |
| `long_idle.txt` | Long idle period before the next arrival |
| `starvation.txt` | Low-priority reader delayed by a stream of high-priority readers |

`tests/expected/` holds the expected output for each input under `FCFS` and `PRIORITY`. These were produced by a separate reference simulator written from the specification and checked by hand, not by this program. To build and run every case:

```bash
./tests/run_tests.sh
```

## Known Limitations

- The input is assumed to be valid. If N is larger than the number of reader records, or a numeric field is not a number, the program crashes instead of printing an error.
- Duplicate IDs, negative arrival times and non-positive service times or priorities are not detected.
- The `state` field in `Process` is not updated during the simulation; the lifecycle is modelled implicitly through start and completion times.
- Algorithm names are case-sensitive (`FCFS`, `PRIORITY`).
- Priority Scheduling has no aging, so low-priority readers can starve (see above).

## Optional Features

None.
