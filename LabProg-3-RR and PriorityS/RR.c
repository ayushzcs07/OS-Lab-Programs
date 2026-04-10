#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n];
    int visited[n];

    float avg_wt = 0, avg_tat = 0;

    printf("Enter Arrival Time and Burst Time:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d AT: ", i+1);
        scanf("%d", &at[i]);

        printf("P%d BT: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
        visited[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100], front = 0, rear = 0;
    int time = 0, completed = 0;

    // Start with first process
    queue[rear++] = 0;
    visited[0] = 1;

    while(completed < n) {
        int i = queue[front++];

        if(rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        // Add newly arrived processes
        for(int j = 0; j < n; j++) {
            if(at[j] <= time && visited[j] == 0) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // Re-add current process if not finished
        if(rt[i] > 0) {
            queue[rear++] = i;
        }

        // If queue empty → jump to next process
        if(front == rear) {
            for(int j = 0; j < n; j++) {
                if(visited[j] == 0) {
                    queue[rear++] = j;
                    visited[j] = 1;
                    time = at[j];
                    break;
                }
            }
        }
    }

    // Calculate TAT and WT
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}

