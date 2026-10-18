/**
 * 
 * SMART LIBRARY
 * Two (2) librarians
 * FCFS, 
 * Priority scheduling (non-preemptive)
 * No concurrency requirements (single-threaded)
 * 
 */

#include <iostream>
#include <queue>
using namespace std;

class Process {
    public:

        // specified attributes

            // process ID as string to allow for alphanumeric IDs as per pdf
            // break tues by lexiographic order.
            std::string pid;

            // arrival time. assuming integer precision
            int arrival_time;

            // scheduling priority (ordinal value, lower = higher priority) 
            int priority;

            // burst time =
            // total amount of execution time required by process
            int service_time; // "reader-service interaction"

            // descriptive category class
            enum class Category{
                STUDENT,
                REGULAR,
                FACULTY,
                RESEARCHER,
                STAFF
            } category;
        
            /*
            
            Lifecycle to follow: NEW → READY → RUNNING → TERMINATED
            
            • NEW to READY when it arrives.
            • READY to RUNNING when selected by the scheduler.
            • RUNNING to TERMINATED when its service time is completed.
        
            */
            enum class State {
                    NEW,
                    READY,
                    RUNNING,
                    WAITING,
                    TERMINATED
                } state;

        // functions (if any)

};

// scheduling functions go here

int main(){

    queue<Process> process_queue;

    // NOTE(!)
    // this is how you would add a process to the queue:
    // either input the details, make the obj and then pass it
    // or just pass the details directly to the constructor like so:
    process_queue.push(Process{"R1", 0, 1, 5, Process::Category::STUDENT, Process::State::NEW}); // R1 is reader 1.. or process id R1
    process_queue.pop();
    return 0;
}
