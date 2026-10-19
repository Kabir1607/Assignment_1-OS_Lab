#include "output.h"

#include <iomanip>

void print_results(std::ostream& out,
                   const std::vector<ProcessMetrics>& metrics,
                   const SummaryMetrics& summary)
{
    out << "PROCESS_ID,ARRIVAL,PRIORITY,SERVICE,START,COMPLETION,WAITING,TURNAROUND,RESPONSE\n";

    for (const ProcessMetrics& m : metrics) {
        out << m.pid << ','
            << m.arrival_time << ','
            << m.priority << ','
            << m.service_time << ','
            << m.start_time << ','
            << m.completion_time << ','
            << m.waiting_time << ','
            << m.turnaround_time << ','
            << m.response_time << '\n';
    }

    // Summary values may be fractional, so print them in fixed decimal form.
    // Six places keep small throughputs (long simulations) from rounding to zero.
    out << std::fixed << std::setprecision(6);
    out << "SUMMARY\n";
    out << "AVERAGE_WAITING," << summary.average_waiting << '\n';
    out << "AVERAGE_TURNAROUND," << summary.average_turnaround << '\n';
    out << "AVERAGE_RESPONSE," << summary.average_response << '\n';
    out << "THROUGHPUT," << summary.throughput << '\n';
    out << "UTILIZATION," << summary.utilization << '\n';
}
