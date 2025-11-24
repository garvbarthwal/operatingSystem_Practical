// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[1024];
};

int main() {
    key_t key = ftok("msgfile", 65);

    int msgid = msgget(key, 0666);

    struct msg_buffer message;

    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

    int bytes_read = strlen(message.msg_text) + 1;   // include '\0'

    printf("Reader received: %s", message.msg_text);
    printf("Reader: Bytes read = %d\n", bytes_read);

    // delete message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}