// writer.c
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

    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    
    message.msg_type = 1;

    printf("Enter message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);  // direct input

    int bytes_written = strlen(message.msg_text) + 1;          // count '\0'

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("Writer: Bytes written = %d\n", bytes_written);

    return 0;
}
