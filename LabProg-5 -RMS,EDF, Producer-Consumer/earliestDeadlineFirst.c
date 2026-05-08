#include <stdio.h>

#define MAX 10
#define SIM_TIME 10

typedef struct {
    int id;
    int exec_time;
    int period;
    int deadline;
    int remaining_time;
    int next_release;
} Task;

int n;
Task tasks[MAX];


void earliestDeadlineFirst() {

    printf("\nEARLIEST DEADLINE FIRST SCHEDULING\n\n");
    printf("%-8s %-15s\n", "Time", "Running Task");
    printf("--------------------------------\n");


    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = 0;
        tasks[i].next_release = 0;
    }

    int current_deadline[MAX];

    for (int i = 0; i < n; i++) {
        current_deadline[i] = tasks[i].deadline;
    }


    for (int t = 0; t < SIM_TIME; t++) {


        for (int i = 0; i < n; i++) {

            if (t == tasks[i].next_release) {

                tasks[i].remaining_time = tasks[i].exec_time;

                current_deadline[i] = t + tasks[i].deadline;

                tasks[i].next_release += tasks[i].period;
            }
        }


        int selected = -1;

        for (int i = 0; i < n; i++) {

            if (tasks[i].remaining_time > 0) {

                if (selected == -1 ||
                    current_deadline[i] < current_deadline[selected]) {

                    selected = i;
                }
            }
        }


        if (selected != -1) {

            printf("%-8d T%d\n", t, tasks[selected].id);

            tasks[selected].remaining_time--;

        } else {

            printf("%-8d Idle\n", t);
        }
    }
}


int main() {

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        tasks[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &tasks[i].exec_time);

        printf("Period: ");
        scanf("%d", &tasks[i].period);

        printf("Deadline: ");
        scanf("%d", &tasks[i].deadline);
    }

    earliestDeadlineFirst();

    return 0;
}
