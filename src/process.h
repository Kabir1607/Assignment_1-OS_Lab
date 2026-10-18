#pragma once

#include <string>


class Process {
    public:

        // specified attributes

            // process ID as string to allow for alphanumeric IDs as per pdf
            // break tie tules by lexiographic order.
            std::string pid;

            // arrival time. assuming integer precision
            int arrival_time;

            // scheduling priority (ordinal value, lower = higher priority) 
            int priority;

            // burst time =
            // total amount of execution time required by process
            int service_time; // "reader-service interaction"

            // descriptive category label from the input file
            std::string category;
        
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
