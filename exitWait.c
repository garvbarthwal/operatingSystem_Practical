#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
    pid_t pid,cpid;
    printf("Original process PID:%d\n",getpid());
    pid=fork();
    if(pid < 0){
        perror("Fork failed!");
        exit(EXIT_FAILURE);
    } if(pid == 0){
        printf("In the child process.\tChild PID:%d\tParent PID:%d.\n",getpid(),getppid());
        printf("Doing some work!\n");
        sleep(2);
        printf("Completed the work.Now exitting normally.\n");
        exit(0);
    } else {
        printf("In the Parent process.\tPID:%d\n",getpid());
        printf("Waiting for child to do the work!\n");
        cpid=wait(NULL);
        printf("Child with PID %d has terminated.\n", cpid);
        printf("Parent process continues after child termination.\n");
        exit(0);
    }
    return 0;
}