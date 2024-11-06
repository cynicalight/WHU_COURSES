#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int i = *((int *) arg);
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", i);
        sleep(1);

        // Grabbing forks
        pthread_mutex_lock(&forks[LEFT]);
        pthread_mutex_lock(&forks[i]);

        // Eating
        printf("Philosopher %d is eating\n", i);
        sleep(1);

        // Releasing forks
        pthread_mutex_unlock(&forks[i]);
        pthread_mutex_unlock(&forks[LEFT]);
    }
    return NULL;
}

int main() {
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &i);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
