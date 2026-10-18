# Smart Library — OS Lab Assignment 1

A simple simulation of readers receiving service from librarians.

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

The full assignment specification is in [docs/OSLab_CS_3710__A1_Specifications.pdf](docs/OSLab_CS_3710__A1_Specifications.pdf).

## Compile and run

```bash
g++ -std=c++17 src/*.cpp -o library
./library input.txt FCFS
./library input.txt PRIORITY
```

Results are stored but are not printed yet.
