#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_burst;
};

void executeProcess(struct Process *process) {
    printf("Executing process %d (Priority: %d, Remaining Burst Time: %d)\n",
           process->id, process->priority, process->remaining_burst);
    process->remaining_burst--;
}

int main() {
    struct Process processes[MAX_PROCESSES] = {
        {1, 0, 5, 3, 5},
        {2, 1, 3, 1, 3},
        {3, 3, 2, 4, 2},
        {4, 5, 4, 2, 4},
        {5, 6, 1, 5, 1}
    };

    int total_processes = sizeof(processes) / sizeof(processes[0]);
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < total_processes) {
        int min_priority = 1000;
        int selected_process = -1;

        for (int i = 0; i < total_processes; i++) {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_burst > 0 &&
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                selected_process = i;
            }
        }

        if (selected_process != -1) {
            executeProcess(&processes[selected_process]);
            current_time++;

            if (processes[selected_process].remaining_burst == 0) {
                completed_processes++;
            }
        } else {
            current_time++; // No process to execute at this time
        }
    }

    printf("All processes completed.\n");

    return 0;
}
