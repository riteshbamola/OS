#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;
    
    // Number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    // Allocate matrices and vectors
    int alloc[n][m], max[n][m], avail[m];
    int need[n][m], safeSeq[n], finish[n];

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum demand matrix
    printf("Enter maximum demand matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter available resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the need matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize finish array to false
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Banker's Algorithm (Safety Check)
    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) { // Process is not yet finished
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        break;
                    }
                }
                if (j == m) { // If all resources can be allocated
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k]; // Release allocated resources
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1; // Mark process as finished
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("The system is in an unsafe state.\n");
            return -1;
        }
    }

    // Print the safe sequence
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    
    return 0;
}
