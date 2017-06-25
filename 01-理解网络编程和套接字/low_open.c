#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

void errorHandling(const char* message);

int main(){
    char message[] = "I love tcp-ip programming!";

    int fd = open("data.txt", O_CREAT|O_TRUNC|O_RDWR);
    if(fd == -1){
        errorHandling("open() error!");
    }
    printf("file descriptor: %d \n", fd);

    int len = write(fd, message, strlen(message));
    if(len == -1){
        errorHandling("write() error!");
    }

    close(fd);
    return 0;
}

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}