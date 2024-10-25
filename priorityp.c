#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[], int quantum) {
    int rem_bt[n]; // Remaining burst time
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];  
        wt[i] = 0; // Initialize waiting time
    }

    int time = 0; // Time elapsed
    int completed = 0; // Count of completed processes

    while (completed < n) {
        int found = 0; // To check if a process is found
        for (int i = 0; i < n; i++) {
            // Only consider processes that have arrived and are not completed
            if (rem_bt[i] > 0 && at[i] <= time) {
                found = 1; // A process is found
                if (rem_bt[i] > quantum) {
                    time += quantum; // Increment time by quantum
                    rem_bt[i] -= quantum; // Decrease remaining burst time
                } else {
                    time += rem_bt[i]; // Increment time by remaining burst time
                    wt[i] = time - bt[i] - at[i]; // Calculate waiting time
                    rem_bt[i] = 0; // Process finished
                    completed++; // Increment completed process count
                }
            }
        }

        // If no process was found, increment time until a process arrives
        if (!found) {
            time++; // No process executed, increment time
        }
    }
}

void findTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // TAT = BT + WT
    }
}

void findAvgTime(int processes[], int n, int bt[], int at[], int quantum) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, at, wt, quantum);
    findTurnaroundTime(processes, n, bt, wt, tat);

    // Print results
    printf("Processes\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i]);
    }

    float total_wt = 0, total_tat = 0; 
    for (int i = 0; i < n; i++) {
        total_wt += wt[i]; 
        total_tat += tat[i];
    }
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3, 4, 5, 6}; 
    int n = sizeof(processes) / sizeof(processes[0]); 
    int burst_time[] = {7, 6, 5, 2, 9, 3}; 
    int arrival_time[] = {6, 5, 4, 2, 3, 1}; // Arrival times
    int quantum = 3; // Time quantum 
    findAvgTime(processes, n, burst_time, arrival_time, quantum); 
    return 0; 
}
