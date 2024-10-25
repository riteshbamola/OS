#include <stdio.h>

void priorityScheduling(int n, int bt[], int at[], int priority[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0, completed = 0, time = 0, shortest;
    int is_completed[n];

    // Initialize is_completed array to 0
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    // Scheduling logic
    while (completed != n) {
        int highest_priority = 10000;
        shortest = -1;

        // Find the process with the highest priority
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !is_completed[i] && priority[i] < highest_priority) {
                highest_priority = priority[i];
                shortest = i;
            }
        }

        // If a process is found
        if (shortest != -1) {
            time += bt[shortest];
            tat[shortest] = time - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            if (wt[shortest] < 0) wt[shortest] = 0;  // Ensure WT is non-negative
            total_wt += wt[shortest];
            total_tat += tat[shortest];
            is_completed[shortest] = 1;  // Mark the process as completed
            completed++;
        } else {
            time++;  // No process is ready; increment time
        }
    }

    // Print process details
    printf("Processes\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, bt[i], at[i], priority[i], wt[i], tat[i]);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n = 4;  // Number of processes
    int burst_time[] = {5, 3, 8, 6};  // Burst times
    int arrival_time[] = {0, 1, 2, 3};  // Arrival times
    int priority[] = {1,3,2,4};  // Priorities

    priorityScheduling(n, burst_time, arrival_time, priority);
    return 0;
}
