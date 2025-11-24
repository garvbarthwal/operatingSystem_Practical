#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t pid;
    printf("Original process PID:%d\n",getpid());
    pid=fork();

    if(pid < 0){
        perror("Fork failed!");
        exit(EXIT_FAILURE);
    } if (pid == 0){
        int sumEven=0;
        for(int i=0;i<50;i+=2){
            sumEven+=i;
        }
        printf("Sum of even number(0-50) is:%d .\nThis is calculated using a child process. PID:%d\tPPID:%d\n",sumEven,getpid(),getppid());
        sleep(1);
    } else{
        int sumOdd=0;
        for(int i=1;i<50;i+=2){
            sumOdd+=i;
        }
        printf("Sum of odd number(0-50) is:%d .\nThis is calculated using a parent process. PID:%d\tPPID:%d\n",sumOdd,getpid(),getppid());
        sleep(1);
    }

    return 0;
}