#pragma once

#include <vector>
#include "process.h"
#include "fcfs.h" // for ProcessResult struct

std::vector<ProcessResult> priority_schedule(std::vector<Process> processes);