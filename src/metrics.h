#pragma once

#include <string>
#include <vector>
#include "fcfs.h" // for ProcessResult

struct ProcessMetrics {
    std::string pid;
    int arrival_time;
    int priority;
    int service_time;
    long long start_time;      // S_i: first start time (all from the assignment)
    long long completion_time; // C_i
    long long turnaround_time; // TAT_i = C_i - A_i
    long long waiting_time;    // WT_i  = TAT_i - B_i
    long long response_time;   // RT_i  = S_i - A_i
};

// simulation metrics:
struct SummaryMetrics {
    double average_waiting;
    double average_turnaround;
    double average_response;
    double throughput;  // processes per  time unit
    double utilization; // % of librarian's time spent busy
};

// Number of identical service units (librarians in our case)
constexpr int SERVICE_UNITS = 2;

// Rows are returned in lexicographic process-ID order
std::vector<ProcessMetrics> compute_process_metrics(const std::vector<ProcessResult>& results);

SummaryMetrics compute_summary_metrics(const std::vector<ProcessMetrics>& metrics);
