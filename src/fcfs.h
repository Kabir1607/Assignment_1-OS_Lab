#pragma once

#include <vector>
#include "process.h"

struct ProcessResult {
    Process process;
    long long start_time;
    long long completion_time;
};

std::vector<ProcessResult> fcfs(std::vector<Process> processes);