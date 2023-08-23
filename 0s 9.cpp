#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    // Generate a key for shared memory
    key_t key = ftok("shm_example", 1234);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get a shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Write data to the shared memory
    strcpy(shm_ptr, "Hello from the parent process!");

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process

        // Attach the shared memory segment to the child's address space
        char *shm_ptr_child = (char *)shmat(shmid, NULL, 0);
        if (shm_ptr_child == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        printf("Child process reads: %s\n", shm_ptr_child);

        // Detach the shared memory segment from the child's address space
        if (shmdt(shm_ptr_child) == -1) {
            perror("shmdt");
            exit(1);
        }

        exit(0);
    } else {
        // Parent process
        // Wait for the child to complete
        wait(NULL);

        printf("Parent process reads: %s\n", shm_ptr);

        // Detach the shared memory segment from the parent's address space
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Deallocate the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}
