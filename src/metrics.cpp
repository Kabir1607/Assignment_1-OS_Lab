#include "metrics.h"

#include <algorithm>

std::vector<ProcessMetrics> compute_process_metrics(const std::vector<ProcessResult>& results)
{
    std::vector<ProcessMetrics> metrics;

    for (const ProcessResult& result : results) {
        const Process& p = result.process;
        ProcessMetrics m{};

        m.pid = p.pid;
        m.arrival_time = p.arrival_time;
        m.priority = p.priority;
        m.service_time = p.service_time;
        m.start_time = result.start_time;
        m.completion_time = result.completion_time;
        m.turnaround_time = m.completion_time - m.arrival_time;
        m.waiting_time = m.turnaround_time - m.service_time;
        m.response_time = m.start_time - m.arrival_time;

        metrics.push_back(m);
    }

    // Output rows must be in lexicographic process-ID order.
    std::sort(metrics.begin(), metrics.end(),
        [](const ProcessMetrics& a, const ProcessMetrics& b) {
            return a.pid < b.pid;
        });

    return metrics;
}

SummaryMetrics compute_summary_metrics(const std::vector<ProcessMetrics>& metrics)
{
    SummaryMetrics summary{};
    if (metrics.empty()) {
        return summary;
    }

    long long total_waiting = 0;
    long long total_turnaround = 0;
    long long total_response = 0;
    long long busy_time = 0; // B: busy time summed across both librarians
    long long first_arrival = metrics.front().arrival_time;
    long long last_completion = metrics.front().completion_time;

    for (const ProcessMetrics& m : metrics) {
        total_waiting += m.waiting_time;
        total_turnaround += m.turnaround_time;
        total_response += m.response_time;
        busy_time += m.service_time;
        first_arrival = std::min(first_arrival, static_cast<long long>(m.arrival_time));
        last_completion = std::max(last_completion, m.completion_time);
    }

    double n = static_cast<double>(metrics.size());
    summary.average_waiting = total_waiting / n;
    summary.average_turnaround = total_turnaround / n;
    summary.average_response = total_response / n;

    // E: elapsed time from the first arrival to the last completion. --> Assuming
    // Always positive, since every service time is at least 1.
    double elapsed = static_cast<double>(last_completion - first_arrival);
    summary.throughput = n / elapsed;
    summary.utilization = busy_time / (SERVICE_UNITS * elapsed) * 100.0;

    return summary;
}
