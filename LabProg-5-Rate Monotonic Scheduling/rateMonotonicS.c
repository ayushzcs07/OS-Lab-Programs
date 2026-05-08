#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int execution;
    int period;
    int remaining;
};

// GCD
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Hyperperiod
int hyperperiod(struct Task t[], int n) {

    int h = t[0].period;

    for (int i = 1; i < n; i++) {
        h = lcm(h, t[i].period);
    }

    return h;
}

// RMS Scheduling
void RMS(struct Task t[], int n, int h) {

    printf("\nRATE MONOTONIC SCHEDULING\n\n");
    printf("%-8s %-15s\n", "Time", "Running Task");
    printf("--------------------------------\n");

    for (int time = 0; time < h; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {

            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
            }
        }

        // Select highest priority task
        int selected = -1;

        for (int i = 0; i < n; i++) {

            if (t[i].remaining > 0) {

                if (selected == -1 ||
                    t[i].period < t[selected].period) {

                    selected = i;
                }
            }
        }

        // Execute selected task
        if (selected != -1) {

            printf("%-8d T%d\n",
                   time,
                   t[selected].id);

            t[selected].remaining--;

        } else {

            printf("%-8d Idle\n", time);
        }
    }
}

int main() {

    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task t[MAX];

    for (int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &t[i].execution);

        printf("Period: ");
        scanf("%d", &t[i].period);

        t[i].remaining = 0;
    }

    int h = hyperperiod(t, n);

    printf("\nHyperperiod = %d\n", h);

    RMS(t, n, h);

    return 0;
}
