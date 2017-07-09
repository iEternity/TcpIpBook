#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char*[]){
    char str1[] = "hello~ zhangkuo!\n";
    char str2[] = "I love programming!\n";

    int fd1 = dup(1);
    int fd2 = dup2(1, 88);

    printf("fd1: %d  fd2: %d \n", fd1, fd2);

    write(fd1, str1, sizeof(str1));
    write(fd2, str2, sizeof(str2));

    close(fd1);
    close(fd2);

    puts(str1);

    close(1);

    puts(str2);

    return 0;
}