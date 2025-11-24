// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo="myfifo";
    int fd=open(fifo,O_RDONLY);

    if(fd < 0){
        perror("read");
        return 1;
    }
    char buffer[100];
    while(1){
        int bytes_read=read(fd,buffer,sizeof(buffer)-1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // manually null terminate
            printf("Reader received: %s", buffer);
            printf("Reader: Bytes read = %d\n", bytes_read);
        } else if (bytes_read == 0) {
            // writer closed the FIFO -> EOF
            printf("No more data, writer closed. Exiting.\n");
            break;
        } else {
            perror("read");
            break;
        }
    }
    close(fd);
    return 0;
}