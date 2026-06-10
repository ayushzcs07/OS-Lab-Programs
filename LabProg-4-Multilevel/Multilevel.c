#include <stdio.h>

#define MAX 100

typedef struct
{
    int id;
    int at, bt, rt;
    int ct, tat, wt;
    int type;              // 0=System, 1=Interactive, 2=Batch
    int last_executed;
} Process;

int main()
{
    Process p[MAX], temp;
    int n;
    int tq = 2;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("\nProcess P%d\n", p[i].id);
        printf("Enter AT, BT and Type (0=System, 1=Interactive, 2=Batch): ");
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].type);

        p[i].rt = p[i].bt;
        p[i].last_executed = -1;
    }

    /* Bubble Sort by Arrival Time */
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;
    int completed = 0;

    int current_p = -1;
    int current_q_count = 0;

    while(completed < n)
    {
        int best_p = -1;

        /* System Queue (Round Robin) */
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time &&
               p[i].type == 0 &&
               p[i].rt > 0)
            {
                if(best_p == -1 ||
                   p[i].last_executed < p[best_p].last_executed)
                {
                    best_p = i;
                }
            }
        }

        /* Continue same RR process until quantum expires */
        if(current_p != -1 &&
           p[current_p].type == 0 &&
           p[current_p].rt > 0 &&
           current_q_count < tq)
        {
            best_p = current_p;
        }

        /* Interactive Queue (FCFS) */
        if(best_p == -1)
        {
            for(int i = 0; i < n; i++)
            {
                if(p[i].at <= time &&
                   p[i].type == 1 &&
                   p[i].rt > 0)
                {
                    best_p = i;
                    break;
                }
            }
        }

        /* Batch Queue (FCFS) */
        if(best_p == -1)
        {
            for(int i = 0; i < n; i++)
            {
                if(p[i].at <= time &&
                   p[i].type == 2 &&
                   p[i].rt > 0)
                {
                    best_p = i;
                    break;
                }
            }
        }

        if(best_p != -1)
        {
            p[best_p].rt--;
            time++;

            if(best_p == current_p)
                current_q_count++;
            else
                current_q_count = 1;

            current_p = best_p;
            p[best_p].last_executed = time;

            if(p[best_p].rt == 0)
            {
                p[best_p].ct = time;
                p[best_p].tat = p[best_p].ct - p[best_p].at;
                p[best_p].wt = p[best_p].tat - p[best_p].bt;

                completed++;

                current_p = -1;
                current_q_count = 0;
            }
            else if(p[best_p].type == 0 &&
                    current_q_count == tq)
            {
                current_p = -1;
                current_q_count = 0;
            }
        }
        else
        {
            time++;
        }
    }

    printf("\n%-8s %-18s %-4s %-4s %-4s %-5s %-5s\n",
           "PID", "Queue", "AT", "BT", "CT", "TAT", "WT");

    float totalTAT = 0, totalWT = 0;

    for(int i = 0; i < n; i++)
    {
        char *qName;

        if(p[i].type == 0)
            qName = "System";
        else if(p[i].type == 1)
            qName = "Interactive";
        else
            qName = "Batch";

        printf("P%-7d %-18s %-4d %-4d %-4d %-5d %-5d\n",
               p[i].id,
               qName,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f",
           totalTAT / n);

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    return 0;
}
        
