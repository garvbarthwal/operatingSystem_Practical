// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    char *shared = (char*) shmat(shmid, NULL, 0);

    printf("Enter message: ");
    fgets(shared, 1024, stdin);   // <-- directly write into shared memory

    int bytes_written = strlen(shared) + 1;  // include '\0'
    printf("Writer: Bytes written = %d\n", bytes_written);

    shmdt(shared);

    return 0;
}
