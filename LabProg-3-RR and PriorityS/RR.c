#include <stdio.h>

struct Process
{
    int pid;
    int at, bt, rt;
    int ct, tat, wt;
    int visited;
};

int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], temp;

    printf("Enter Arrival Time and Burst Time:\n");
    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("P%d AT: ", p[i].pid);
        scanf("%d", &p[i].at);

        printf("P%d BT: ", p[i].pid);
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;
        p[i].visited = 0;
    }

    /* Sort by Arrival Time */
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

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100];
    int front = 0, rear = 0;

    int time = p[0].at;
    int completed = 0;

    queue[rear++] = 0;
    p[0].visited = 1;

    while(completed < n)
    {
        int i = queue[front++];

        if(p[i].rt > tq)
        {
            time += tq;
            p[i].rt -= tq;
        }
        else
        {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        }

        /* Add newly arrived processes */
        for(int j = 0; j < n; j++)
        {
            if(p[j].at <= time && p[j].visited == 0)
            {
                queue[rear++] = j;
                p[j].visited = 1;
            }
        }

        /* Re-add current process if unfinished */
        if(p[i].rt > 0)
        {
            queue[rear++] = i;
        }

        /* If ready queue becomes empty */
        if(front == rear)
        {
            for(int j = 0; j < n; j++)
            {
                if(p[j].visited == 0)
                {
                    queue[rear++] = j;
                    p[j].visited = 1;
                    time = p[j].at;
                    break;
                }
            }
        }
    }

    float avg_wt = 0, avg_tat = 0;

    for(int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
