#include <stdio.h>

int main() {
    int n, i, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], pid[n];

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Enter Burst Time: ");
        scanf("%d", &BT[i]);
        pid[i] = i + 1;
    }

    printf("\nChoose Scheduling Method\n");
    printf("1. SJF Non-Preemptive\n");
    printf("2. SJF Preemptive (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {

        case 1: {   // Non-Preemptive SJF
            int CT[n], TAT[n], WT[n], completed[n];
            int current_time = 0, done = 0;
            float totalWT = 0, totalTAT = 0;

            for(i = 0; i < n; i++)
                completed[i] = 0;

            while(done < n) {
                int idx = -1, minBT = 9999;

                for(i = 0; i < n; i++) {
                    if(AT[i] <= current_time && completed[i] == 0) {
                        if(BT[i] < minBT) {
                            minBT = BT[i];
                            idx = i;
                        }
                    }
                }

                if(idx == -1)
                    current_time++;
                else {
                    CT[idx] = current_time + BT[idx];
                    TAT[idx] = CT[idx] - AT[idx];
                    WT[idx] = TAT[idx] - BT[idx];

                    totalWT += WT[idx];
                    totalTAT += TAT[idx];

                    completed[idx] = 1;
                    current_time = CT[idx];
                    done++;
                }
            }

            printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
            for(i = 0; i < n; i++)
                printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                       pid[i], AT[i], BT[i], CT[i], WT[i], TAT[i]);

            printf("\nAverage WT = %.2f", totalWT/n);
            printf("\nAverage TAT = %.2f\n", totalTAT/n);

            break;
        }

        case 2: {   // Preemptive SJF (SRTF)
            int RT[n], CT[n], TAT[n], WT[n];
            int current_time = 0, completed = 0;
            float totalWT = 0, totalTAT = 0;

            for(i = 0; i < n; i++)
                RT[i] = BT[i];

            while(completed < n) {
                int idx = -1, minRT = 9999;

                for(i = 0; i < n; i++) {
                    if(AT[i] <= current_time && RT[i] > 0) {
                        if(RT[i] < minRT) {
                            minRT = RT[i];
                            idx = i;
                        }
                    }
                }

                if(idx == -1)
                    current_time++;
                else {
                    RT[idx]--;
                    current_time++;

                    if(RT[idx] == 0) {
                        completed++;

                        CT[idx] = current_time;
                        TAT[idx] = CT[idx] - AT[idx];
                        WT[idx] = TAT[idx] - BT[idx];

                        totalWT += WT[idx];
                        totalTAT += TAT[idx];
                    }
                }
            }

            printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
            for(i = 0; i < n; i++)
                printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                       pid[i], AT[i], BT[i], CT[i], WT[i], TAT[i]);

            printf("\nAverage WT = %.2f", totalWT/n);
            printf("\nAverage TAT = %.2f\n", totalTAT/n);

            break;
        }

        default:
            printf("Invalid Choice\n");
    }

    return 0;
}
