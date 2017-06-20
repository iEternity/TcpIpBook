#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void errorHandling(const char* message);

int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sockClient = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(connect(sockClient, (sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        errorHandling("connect() error!");
    }
    else{
        puts("client connect success...");
    }

    write(sockClient, "123", strlen("1234"));
    send(sockClient, "4", strlen("4"), MSG_OOB);
    write(sockClient, "567", strlen("567"));
    send(sockClient, "890", strlen("890"), MSG_OOB);

    close(sockClient);

    return 0;
}

void errorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}