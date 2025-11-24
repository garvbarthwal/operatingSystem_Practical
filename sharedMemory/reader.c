// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, 1024, 0666);

    char *shared = (char*) shmat(shmid, NULL, 0);

    int bytes_read = strlen(shared) + 1;  // include '\0'

    printf("Reader received: %s", shared);
    printf("Reader: Bytes read = %d\n", bytes_read);

    shmdt(shared);

    // remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
