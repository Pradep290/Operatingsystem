#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define TIME_QUANTUM 2

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst;
    int waiting_time;
    int turnaround_time;
};

void executeProcess(struct Process *process, int current_time) {
    int executed_time = TIME_QUANTUM;
    if (process->remaining_burst < TIME_QUANTUM) {
        executed_time = process->remaining_burst;
    }

    printf("Executing process %d (Remaining Burst Time: %d)\n", process->id, process->remaining_burst);
    process->remaining_burst -= executed_time;

    process->waiting_time += current_time - process->arrival_time;
    current_time += executed_time;

    if (process->remaining_burst == 0) {
        process->turnaround_time = current_time - process->arrival_time;
    }
}

int main() {
    struct Process processes[MAX_PROCESSES] = {
        {1, 0, 6, 6, 0, 0},
        {2, 1, 8, 8, 0, 0},
        {3, 2, 7, 7, 0, 0},
        {4, 3, 3, 3, 0, 0},
        {5, 4, 4, 4, 0, 0}
    };

    int total_processes = sizeof(processes) / sizeof(processes[0]);
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < total_processes) {
        for (int i = 0; i < total_processes; i++) {
            if (processes[i].remaining_burst > 0) {
                executeProcess(&processes[i], current_time);
                if (processes[i].remaining_burst == 0) {
                    completed_processes++;
                }
            }
        }
    }

    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < total_processes; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }

    return 0;
}
