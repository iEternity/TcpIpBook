#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void errorHandling(const char * message);

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sock, (struct sockaddr*)& sockAddr, sizeof(sockAddr)) == -1){
        errorHandling("bind() error!");
    }

    char buf[256];
    while(1){
        int readLen = recvfrom(sock, buf, sizeof(buf)-1, 0, 0, 0);
        if(readLen > 0){
            buf[readLen] = 0;
            fputs(buf, stdout);
        }
        else{
            break;
        }
    }

    close(sock);
    return 0;
}

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}