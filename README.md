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

- `src/main.cpp`: Creates an example reader and calls the FCFS function.
- `src/process.h`: Defines the shared process fields, reader categories, and process states.
- `src/fcfs.h`: Declares the FCFS function and defines its result structure.
- `src/fcfs.cpp`: Implements FCFS for two librarians and returns each reader's start and completion times.

The full assignment specification is in [docs/OSLab_CS_3710__A1_Specifications.pdf](docs/OSLab_CS_3710__A1_Specifications.pdf).
