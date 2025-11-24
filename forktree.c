#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
    pid_t pid1,pid2,pid3;
    printf("Original process PID: %d\n",getpid());
    pid1=fork();
    
    if(pid1 < 0){
        perror("Fork failed!");
        exit(EXIT_FAILURE);
    }
    if(pid1 == 0){
        printf("Child 1 created.PID:%d\n",getpid());
         
        pid2=fork();
        if(pid2 < 0){
        perror("Fork failed!");
        exit(EXIT_FAILURE);
        }
        if(pid2 == 0){
            printf("Grandchild1 (1.1) created.PID:%d  PPID:%d\n",getpid(),getppid());
        }
    }
    else{
        pid2=fork();
        if(pid2 < 0){
        perror("Fork failed!");
        exit(EXIT_FAILURE);
        }
        if(pid2 == 0){
            printf("Child 2 created.PID:%d  PPID:%d\n",getpid(),getppid());
        }
    }
    sleep(3);
    printf("Process PID: %d is terminating.\n", getpid());
    return 0;
}