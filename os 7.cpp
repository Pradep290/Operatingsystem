#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void executeProcess(struct Process *process, int current_time) {
    printf("Executing process %d (Burst Time: %d)\n", process->id, process->burst_time);
    process->waiting_time = current_time - process->arrival_time;
    process->turnaround_time = process->waiting_time + process->burst_time;
}

int main() {
    struct Process processes[MAX_PROCESSES] = {
        {1, 0, 6, 0, 0},
        {2, 1, 8, 0, 0},
        {3, 2, 7, 0, 0},
        {4, 3, 3, 0, 0},
        {5, 4, 4, 0, 0}
    };

    int total_processes = sizeof(processes) / sizeof(processes[0]);
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < total_processes) {
        int shortest_job = -1;
        int shortest_burst = 1000;

        for (int i = 0; i < total_processes; i++) {
            if (processes[i].arrival_time <= current_time &&
                processes[i].burst_time > 0 &&
                processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_job = i;
            }
        }

        if (shortest_job != -1) {
            executeProcess(&processes[shortest_job], current_time);
            current_time += processes[shortest_job].burst_time;
            completed_processes++;
            processes[shortest_job].burst_time = 0; // Mark process as completed
        } else {
            current_time++; // No process to execute at this time
        }
    }

    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < total_processes; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }

    return 0;
}
