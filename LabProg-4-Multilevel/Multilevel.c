#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt, ct, wt, tat, type;
    int last_executed;
} Process;

// Types: 0 = System (RR), 1 = Interactive (FCFS), 2 = Batch (FCFS)
Process p[MAX];
int n, tq = 2;

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d\n", p[i].id);
        printf("Enter AT, BT, and Type (0=System, 1=Interactive, 2=Batch): ");
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].type);
        p[i].rt = p[i].bt;
        p[i].last_executed = -1;
    }

    int time = 0, completed = 0;
    int current_p = -1;
    int current_q_count = 0;

    while (completed < n) {
        int best_p = -1;

        // 1. System Queue (RR)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].type == 0 && p[i].rt > 0) {
                if (best_p == -1 || p[i].last_executed < p[best_p].last_executed) {
                    best_p = i;
                }
            }
        }

        if (current_p != -1 && p[current_p].type == 0 && p[current_p].rt > 0 && current_q_count < tq) {
            best_p = current_p;
        }

        // 2. Interactive Queue (FCFS)
        if (best_p == -1) {
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].type == 1 && p[i].rt > 0) {
                    best_p = i;
                    break;
                }
            }
        }

        // 3. Batch Queue (FCFS)
        if (best_p == -1) {
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].type == 2 && p[i].rt > 0) {
                    best_p = i;
                    break;
                }
            }
        }

        if (best_p != -1) {
            p[best_p].rt--;
            time++;
            current_q_count++;
            p[best_p].last_executed = time;
            current_p = best_p;

            if (p[best_p].rt == 0) {
                p[best_p].ct = time;
                p[best_p].tat = p[best_p].ct - p[best_p].at;
                p[best_p].wt = p[best_p].tat - p[best_p].bt;
                completed++;
                current_p = -1;
            } else if (p[best_p].type == 0 && current_q_count == tq) {
                current_p = -1;
            }
        } else {
            time++;
        }
    }

    // Table Output
    printf("\n%-10s %-20s %-3s %-3s %-3s %-12s %-10s\n",
           "Process", "Queue", "AT", "BT", "CT", "TAT (CT-AT)", "WT (TAT-BT)");

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        char *qName = (p[i].type == 0) ? "System Queue" :
                      (p[i].type == 1) ? "Interactive Queue" : "Batch Queue";

        printf("P%-9d %-20s %-3d %-3d %-3d %-12d %-10d\n",
               p[i].id, qName, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Turnaround Time = %.2f ms", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f ms\n", totalWT / n);

    return 0;
}
