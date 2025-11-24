#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("\n========== Orphan Process Demo ==========\n");
    printf("Parent PID: %d\n", getpid());
    fflush(stdout);

    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Parent process exits after short delay
        printf("\n--- Orphan Demo: Parent Process ---\n");
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        printf("Parent is exiting before child...\n");
        exit(0);
        
    }

    if (pid == 0) {
        // Child process
        sleep(6);  // Ensure parent terminates first
        printf("\n--- Orphan Demo: Child Process ---\n");
        printf("Child PID: %d, New Parent PID (init): %d\n", getpid(), getppid());
        printf("Child continues execution after parent is gone.\n");
    }

    sleep(10);  // Allow child to finish before program exits
    return 0;
}