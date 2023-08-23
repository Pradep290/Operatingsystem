#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Function to be executed by each thread
void *threadFunction(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d is running\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("All threads have completed\n");

    return 0;
}
