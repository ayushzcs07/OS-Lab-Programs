#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

pthread_mutex_t chopstick[MAX];
pthread_mutex_t print_lock;

int N;

void safe_print(const char* msg, int id) {
    pthread_mutex_lock(&print_lock);
    printf(msg, id);
    pthread_mutex_unlock(&print_lock);
}

void* philosopher(void* num) {
    int id = *(int*)num;

    for (int i = 0; i < 3; i++) {  // limited cycles
        safe_print("Philosopher %d is thinking\n", id);
        sleep(1);

        if (id % 2 == 0) {
            pthread_mutex_lock(&chopstick[id]);
            pthread_mutex_lock(&chopstick[(id + 1) % N]);
        } else {
            pthread_mutex_lock(&chopstick[(id + 1) % N]);
            pthread_mutex_lock(&chopstick[id]);
        }

        safe_print("Philosopher %d is eating\n", id);
        sleep(2);

        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id + 1) % N]);

        safe_print("Philosopher %d finished eating\n", id);
    }
    return NULL;
}

int main() {
    pthread_t ph[MAX];
    int ids[MAX];

    printf("Enter number of philosophers (max %d): ", MAX);
    scanf("%d", &N);

    if (N > MAX || N < 2) {
        printf("Invalid number.\n");
        return 1;
    }

    pthread_mutex_init(&print_lock, NULL);

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }
    
for (int i = 0; i < N; i++)
{
    pthread_mutex_destroy(&chopstick[i]);
}

pthread_mutex_destroy(&print_lock);



    return 0;
}
