#include <stdio.h>

int main() {
    int bt[10] = {0}, at[10] = {0}, tat[10] = {0}, ct[10] = {0}, wt[10] = {0};
    int n;
    float totalTAT = 0, totalWT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time for each process:\n\n");

    for (int i = 0; i < n; i++) {
        printf("Arrival time of process[%d]: ", i + 1);
        scanf("%d", &at[i]);

        printf("Burst time of process[%d]: ", i + 1);
        scanf("%d", &bt[i]);

        printf("\n");
    }

    // Calculate the completion time of each process
    int sum = at[0];  // Initialize sum with arrival time of the first process
    for (int j = 0; j < n; j++) {
        sum = sum + bt[j];
        ct[j] = sum;
    }

    // Calculate the turnaround time for each process
    for (int k = 0; k < n; k++) {
        tat[k] = ct[k] - at[k];  // TAT = Completion Time - Arrival Time
        totalTAT = totalTAT + tat[k];  // Sum of TAT for average
    }

    // Calculate the waiting time for each process
    for (int k = 0; k < n; k++) {
        wt[k] = tat[k] - bt[k];  // WT = TAT - Burst Time
        totalWT = totalWT + wt[k];  // Sum of WT for average
    }

    // Print the results
    printf("Solution: \n\n");
    printf("P#\t AT\t BT\t CT\t TAT\t WT\t\n\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t %d\t %d\t %d\t %d\t %d\t\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\n\nAverage Turnaround Time = %.2f\n", totalTAT / n);
    printf("\n\nAverage Waiting Time = %.2f\n\n", totalWT / n);

    return 0;
}
