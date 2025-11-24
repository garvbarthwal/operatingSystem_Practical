#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("========== Zombie Process Demo ==========\n");

    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {
        // Child process
        printf("\n--- Zombie Demo: Child Process ---\n");
        printf("Child PID: %d\n", getpid());
        printf("Child is exiting...\n");
        exit(0);  // Child exits immediately
    }

    else {
        // Parent process does NOT call wait()
        printf("\n--- Zombie Demo: Parent Process ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child created with PID: %d\n", pid);
        printf("Parent is sleeping for 5 seconds (not calling wait)...\n");

        sleep(5);  // During this time, the child becomes a zombie
    }
    system("ps -ef");
    return 0;
}