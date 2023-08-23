#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    processes[0].completion_time = processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = 0;
    total_waiting_time += processes[0].waiting_time;
    total_turnaround_time += processes[0].turnaround_time;

    for (int i = 1; i < n; i++) {
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
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
    }

    calculateTimes(processes, n);

    return 0;
}
