#include "fcfs.h"

#include <algorithm>
#include <array>

std::vector<ProcessResult> fcfs(std::vector<Process> processes)
{
    // Earlier arrival first; equal arrivals use lexicographic ID.
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            if (a.arrival_time != b.arrival_time) {
                return a.arrival_time < b.arrival_time;
            }
            return a.pid < b.pid;
        });

    std::array<long long, 2> available_at = {0, 0};
    std::vector<ProcessResult> results;

    for (const Process& process : processes) {
        // Choose the librarian who becomes free first.
        int librarian =
            (available_at[0] <= available_at[1]) ? 0 : 1;

        // A reader must have arrived, and a librarian must be free.
        long long start = std::max(
            available_at[librarian],
            static_cast<long long>(process.arrival_time)
        );

        long long completion = start + process.service_time;

        available_at[librarian] = completion;
        results.push_back({process, start, completion});
    }

    return results;
}