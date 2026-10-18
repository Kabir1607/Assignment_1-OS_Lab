#include "fcfs.h" // for ProcessResult
#include "process.h"
#include <algorithm>
#include <array>
#include <vector>

std::vector<ProcessResult> priority_schedule(std::vector<Process> processes) {
    std::array<long long, 2> available_at = {0, 0};
    std::vector<ProcessResult> results;

    while (!processes.empty()) {
        // 1. Pick the librarian who becomes free first
        int lib = (available_at[0] <= available_at[1]) ? 0 : 1;
        long long current_time = available_at[lib];

        // 2. If no process has arrived by current_time, jump to the earliest arrival
        auto has_arrived = [current_time](const Process& p) {
            return p.arrival_time <= current_time;
        };

        if (std::none_of(processes.begin(), processes.end(), has_arrived)) {
            auto earliest = std::min_element(processes.begin(), processes.end(),
                [](const Process& a, const Process& b) {
                    return a.arrival_time < b.arrival_time;
                });
            current_time = earliest->arrival_time;
        }

        // 3. Among arrived processes, pick best by Priority -> Arrival -> PID
        auto best = processes.end();
        for (auto it = processes.begin(); it != processes.end(); ++it) {
            if (it->arrival_time > current_time) continue;
            if (best == processes.end() ||
                it->priority < best->priority ||
                (it->priority == best->priority && it->arrival_time < best->arrival_time) ||
                (it->priority == best->priority && it->arrival_time == best->arrival_time &&
                 it->pid < best->pid)) {
                best = it;
            }
        }

        // 4. Schedule
        long long start = current_time;
        long long completion = start + best->service_time;
        available_at[lib] = completion;

        results.push_back({*best, start, completion});
        processes.erase(best);
    }

    return results;
}