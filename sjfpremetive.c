#include <stdio.h>

// Function to calculate the average waiting time and turnaround time
void findavgTime(int processes[], int n, int bt[], int at[]) {
    int rt[n];  // Remaining times
    int complete = 0, minm = 10000, shortest = 0, time = 0, finish_time;
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int check = 0;

    // Initialize remaining times as burst times
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    // Processing until all processes are complete
    while (complete != n) {
        minm = 10000;  // Reset the minimum time for this cycle
        check = 0;

        // Find the process with the shortest remaining time
        for (int j = 0; j < n; j++) {
            if ((at[j] <= time) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        // If no process is ready, increment time and continue
        if (check == 0) {
            time++;
            continue;
        }

        // Decrement remaining time of the shortest job
        rt[shortest]--;

        // If the process is complete
        if (rt[shortest] == 0) {
            complete++;
            finish_time = time + 1;  // Current time + 1 as we just finished a unit of time

            // Calculate waiting time for the completed process
            wt[shortest] = finish_time - bt[shortest] - at[shortest];

            // Waiting time can't be negative
            if (wt[shortest] < 0) {
                wt[shortest] = 0;
            }
        }

        // Increment time after each cycle
        time++;
    }

    // Calculate turnaround time and total waiting/turnaround time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround time = Burst time + Waiting time
        total_wt += wt[i];       // Accumulate total waiting time
        total_tat += tat[i];     // Accumulate total turnaround time
    }

    // Output process details and calculated times
    printf("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], at[i], wt[i], tat[i]);
    }

    // Output average waiting time and average turnaround time
    printf("\nAverage waiting time = %.2f", (float) total_wt / n);
    printf("\nAverage turnaround time = %.2f\n", (float) total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3, 4};  // Process IDs
    int n = sizeof(processes) / sizeof(processes[0]);  // Number of processes
    int burst_time[] = {7, 4, 2, 6};  // Burst time for each process
    int arrival_time[] = {0, 1,2,3};  // Arrival time for each process

    // Calculate and display average waiting and turnaround times
    findavgTime(processes, n, burst_time, arrival_time);

    return 0;
}
