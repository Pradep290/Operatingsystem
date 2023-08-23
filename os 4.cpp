#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10

struct Process {
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
};

int findNextProcess(struct Process processes[], int n, int current_time) {
    int shortest_job = -1;
    int shortest_burst_time = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!processes[i].is_completed && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst_time) {
            shortest_job = i;
            shortest_burst_time = processes[i].burst_time;
        }
    }

    return shortest_job;
}

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    while (true) {
        int next_process = findNextProcess(processes, n, current_time);

        if (next_process == -1)
            break;

        processes[next_process].completion_time = current_time + processes[next_process].burst_time;
        processes[next_process].turnaround_time = processes[next_process].completion_time - processes[next_process].arrival_time;
        processes[next_process].waiting_time = processes[next_process].turnaround_time - processes[next_process].burst_time;
        total_waiting_time += processes[next_process].waiting_time;
        total_turnaround_time += processes[next_process].turnaround_time;
        
        current_time = processes[next_process].completion_time;
        processes[next_process].is_completed = true;
    }

    double average_waiting_time = (double) total_waiting_time / n;
    double average_turnaround_time = (double) total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    struct Process processes[MAX_PROCESSES];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].is_completed = false;
    }

    calculateTimes(processes, n);

    return 0;
}
