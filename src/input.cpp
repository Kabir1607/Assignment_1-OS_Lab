#include "input.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Process> read_input(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!std::getline(file, line)) {
        std::cerr << "Input file is empty or could not be opened.\n";
        return {};
    }

    int count = std::stoi(line);
    std::getline(file, line); // Read Q; Library does not use it.

    std::vector<Process> processes;
    for (int i = 0; i < count; ++i) {
        std::getline(file, line);
        std::stringstream row(line);
        Process process{};
        std::string value;

        std::getline(row, process.pid, ',');
        std::getline(row, value, ',');
        process.arrival_time = std::stoi(value);
        std::getline(row, value, ',');
        process.priority = std::stoi(value);
        std::getline(row, value, ',');
        process.service_time = std::stoi(value);
        std::getline(row, process.category);
        process.state = Process::State::NEW;

        processes.push_back(process);
    }

    return processes;
}
