
#include <stdio.h>
#include <limits.h>

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n], rt[n];

    printf("Enter Arrival Time, Burst Time and Priority:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d AT: ", i+1);
        scanf("%d", &at[i]);

        printf("P%d BT: ", i+1);
        scanf("%d", &bt[i]);

        printf("P%d Priority: ", i+1);
        scanf("%d", &pr[i]);

        rt[i] = bt[i];
    }

    printf("\n1. Non-Preemptive Priority\n2. Preemptive Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int completed = 0, time = 0;

    switch(choice) {


    case 1: {
        int done[n];
        for(int i = 0; i < n; i++) done[i] = 0;

        while(completed < n) {
            int idx = -1;
            int highest = INT_MAX;

            for(int i = 0; i < n; i++) {
                if(at[i] <= time && done[i] == 0) {
                    if(pr[i] < highest) {
                        highest = pr[i];
                        idx = i;
                    }
                }
            }

            if(idx != -1) {
                time += bt[idx];
                ct[idx] = time;
                done[idx] = 1;
                completed++;
            } else {
                time++;
            }
        }
        break;
    }


    case 2: {
        while(completed < n) {
            int idx = -1;
            int highest = INT_MAX;

            for(int i = 0; i < n; i++) {
                if(at[i] <= time && rt[i] > 0) {
                    if(pr[i] < highest) {
                        highest = pr[i];
                        idx = i;
                    }
                }
            }

            if(idx != -1) {
                rt[idx]--;
                time++;

                if(rt[idx] == 0) {
                    ct[idx] = time;
                    completed++;
                }
            } else {
                time++;
            }
        }
        break;
    }

    default:
        printf("Invalid choice\n");
        return 0;
    }


    float avg_wt = 0, avg_tat = 0;

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess AT BT PR CT TAT WT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
