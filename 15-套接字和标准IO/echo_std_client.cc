#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void errorHandler(const char* message){
    perror(message);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc !=3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(-1 == connect(sock, (sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandler("connect error");
    }

    FILE* readfp = fdopen(sock, "r");
    FILE* writefp = fdopen(sock, "w");

    char buf[1024];
    int readLen = 0;
    while(1){
        fgets(buf, sizeof(buf), stdin);
        fputs(buf, writefp);
        fflush(writefp);
        fgets(buf, sizeof(buf), readfp);
        printf("Message from server: %s", buf);
    }

    close(sock);
    return 0;
}