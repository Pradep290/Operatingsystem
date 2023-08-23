#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Create a new process using fork()
    pid_t child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process:\n");
        printf("Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent process:\n");
        printf("Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", child_pid);
    }

    return 0;
}
