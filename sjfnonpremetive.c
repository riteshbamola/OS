#include <stdio.h> 

// Function to calculate waiting times
void findWaitingTime(int n, int bt[], int at[], int wt[]) { 
    int completed[n], time = 0, min_bt, shortest, completed_count = 0; 

    // Initialize completed array to 0 (not completed)
    for (int i = 0; i < n; i++) { 
        completed[i] = 0;    
    }

    // Run the loop until all processes are completed
    while (completed_count < n) { 
        shortest = -1; 
        min_bt = 10000;  // Set a high value to find the minimum burst time
        
        // Find the process with the shortest burst time that has arrived and not completed
        for (int j = 0; j < n; j++) { 
            if (at[j] <= time && !completed[j] && bt[j] < min_bt) { 
                min_bt = bt[j]; 
                shortest = j;
            }
        }

        // If no process is ready to be executed, increment the time
        if (shortest == -1) { 
            time++; 
            continue;
        } 

        // Process the selected job
        time += bt[shortest];  // Move time forward by the burst time of the selected process
        wt[shortest] = time - at[shortest] - bt[shortest];  // Calculate waiting time
        completed[shortest] = 1;  // Mark the process as completed
        completed_count++;  // Increment the count of completed processes
    }
}

// Function to calculate turnaround times
void findTurnaroundTime(int n, int bt[], int wt[], int tat[]) { 
    for (int i = 0; i < n; i++) { 
        tat[i] = bt[i] + wt[i];  // Turnaround time = Burst time + Waiting time
    }
}

int main() { 
    int processes[] = {1, 2, 3, 4}; 
    int n = sizeof(processes) / sizeof(processes[0]);  // Number of processes

    int burst_time[] = {5, 3, 8, 6};  // Burst time for each process
    int arrival_time[] = {0, 1, 2, 3};  // Arrival time for each process

    int wt[n], tat[n];  // Arrays for waiting time and turnaround time
    int total_wt = 0, total_tat = 0;  // Totals for calculating averages

    // Find waiting times and turnaround times
    findWaitingTime(n, burst_time, arrival_time, wt); 
    findTurnaroundTime(n, burst_time, wt, tat);

    // Print the table header with tabs for proper alignment
    printf("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");

    // Print details of each process and calculate total waiting and turnaround times
    for (int i = 0; i < n; i++) { 
        total_wt += wt[i]; 
        total_tat += tat[i]; 
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                i + 1, burst_time[i], arrival_time[i], wt[i], tat[i]);
    }

    // Calculate and print average waiting and turnaround times
    printf("\nAverage waiting time = %.2f", (float)total_wt / n); 
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / n);

    return 0;
}
