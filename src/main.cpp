/**
 * 
 * SMART LIBRARY
 * Two (2) librarians
 * FCFS, 
 * Priority scheduling (non-preemptive)
 * No concurrency requirements (single-threaded)
 * 
 */

#include <iostream>
#include <string>
#include <vector>

#include "fcfs.h"
#include "input.h"
#include "metrics.h"
#include "output.h"
#include "priority.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " INPUT_FILE FCFS|PRIORITY\n";
        return 1;
    }

    std::vector<Process> processes = read_input(argv[1]);
    if (processes.empty()) {
        return 1;
    }

    std::string algorithm = argv[2];
    std::vector<ProcessResult> results;

    if (algorithm == "FCFS") {
        results = fcfs(processes);
    } else if (algorithm == "PRIORITY") {
        results = priority_schedule(processes);
    } else {
        std::cerr << "Choose FCFS or PRIORITY.\n";
        return 1;
    }

    std::vector<ProcessMetrics> metrics = compute_process_metrics(results);
    SummaryMetrics summary = compute_summary_metrics(metrics);
    print_results(std::cout, metrics, summary);

    return 0;
}
