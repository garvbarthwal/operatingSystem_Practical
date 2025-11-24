#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(){
    const char *fifo="myfifo";
    mkfifo(fifo,0666);
    int fd=open(fifo,O_WRONLY);

    if(fd < 0){
        perror("open");
        return 1;
    } 

    char msg[100];
    while(1){
        printf("Enter a string ( 'exit' to quit )");
        if(!fgets(msg,sizeof(msg),stdin))
            break;
        
        if(strcmp(msg,"exit\n") == 0){
            break;
        }
        int len=strlen(msg);
        int bytes_writen=write(fd,msg,len);
        if(bytes_writen < 0){
            perror("write");
            return 1;
        }
        printf("Writer Bytes written:%d",bytes_writen);
    }
    close(fd);
    return 0;
}