/**
 * 
 * SMART LIBRARY
 * Two (2) librarians
 * FCFS, 
 * Priority scheduling (non-preemptive)
 * No concurrency requirements (single-threaded)
 * 
 */

#include <vector>

#include "fcfs.h"
#include "process.h"

    
// scheduling functions go here

int main(){

    std::vector<Process> processes;

    // NOTE(!)
    // this is how you would add a process to the vector:
    // either input the details, make the obj and then pass it
    // or just pass the details directly to the constructor like so:
    processes.push_back(Process{"R1", 0, 1, 5, Process::Category::STUDENT, Process::State::NEW}); // R1 is reader 1.. or process id R1

    std::vector<ProcessResult> results = fcfs(processes);
    return 0;
}
