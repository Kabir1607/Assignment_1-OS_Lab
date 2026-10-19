#pragma once

#include <ostream>
#include <vector>
#include "metrics.h"

// Prints the machine-readable result described in Section 15 of the spec.
void print_results(std::ostream& out,
                   const std::vector<ProcessMetrics>& metrics,
                   const SummaryMetrics& summary);
