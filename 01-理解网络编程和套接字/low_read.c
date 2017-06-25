#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

void errorHandling(const char* message);

int main(){
    int fd = open("data.txt", O_RDONLY);
    if(fd == -1){
        errorHandling("open() error!");
    }

    char buf[128];
    int readLen = read(fd, buf, sizeof(buf)-1);
    if(readLen == -1){
        errorHandling("read() error!");
    }

    buf[readLen] = 0;
    puts(buf);

    close(fd);
    
    return 0;
}

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}