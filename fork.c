#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
    pid_t pid;
    printf("Original process (parent) PID: %d\n",getpid());
    pid=fork();
    if(pid < 0 ){
        perror("Fork failed!");
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        printf("Child pid printed from child. PID: %d\n",getpid());
        printf("Parent pid printed from child. PID: %d\n",getppid());
    } else {
        printf("Child pid printed from parent. PID: %d\n",pid);
        printf("Parent pid printed from parent. PID: %d\n",getpid());
    }
    return 0;
}