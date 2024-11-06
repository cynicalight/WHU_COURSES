#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 50000


void* print_hello(void* thread_id) {
    long tid;
    tid = (long)thread_id;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello, (void*)t);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join(threads[t], NULL);
    }

    pthread_exit(NULL);
}
