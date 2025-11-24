#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buffer[100];

    printf("Enter a string: ");
    if(!fgets(buffer,sizeof(buffer),stdin)){
        perror("write");
        exit(1);
    }

    if(pipe(fd) == -1){
        perror("pipe");
        exit(1);
    }

    pid_t p=fork();
    if(p < 0){
        printf("FOrk failed");
        exit(1);
    }

    if(p > 0){
        close(fd[0]);

        int len=strlen(buffer);
        write(fd[1],buffer,len);
        printf("Writer.Writing into the pipe.\n");
        printf("No of bytes: %d\n",len);
        close(fd[1]);
        wait(NULL);
    } else {
        close(fd[1]);
        int len=read(fd[0],buffer,sizeof(buffer)-1);
        buffer[len]='\0';
        printf("In reader. Reading the pipe\n");
        printf("Msg received: %s", buffer);
        printf("No of bytes: %d\n", len);
        close(fd[0]);
    }
    return 0;
}
