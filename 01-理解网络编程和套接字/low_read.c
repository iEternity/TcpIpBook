#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUF_SIZE 100
void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    char buf[BUF_SIZE];

    int fd = open("data.txt",O_RDONLY);
    if(fd == -1){
        error_handling("open() error");
    }
    printf("file descriptor: %d \n",fd);

    if(read(fd, buf, BUF_SIZE) == -1){
        error_handling("read() error");
    }

    printf("file data: %s \n", buf);
    close(fd);
    return 0;
}