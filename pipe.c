#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>

int main(){

    int fd[2];
    char buffer[100];
    printf("Enter input string:");
    scanf("%[^\n]",buffer);

    pipe(fd);
    pid_t p=fork();
    if(p > 0){
        printf("\nWriting on the pipe\n");
        printf("No of bytes : %d\n",(int)strlen(buffer));
        write(fd[1],buffer,strlen(buffer));
    } else if(p == 0){
        printf("\nReading from the pipe\n");
        int n=read(fd[0],buffer,strlen(buffer));
        printf("Msg Received: %s\n",buffer);
        printf("No of bytes received: %d",n);
    } else {
        printf("Fork() sys call failed");
    }
    return 0; 
}