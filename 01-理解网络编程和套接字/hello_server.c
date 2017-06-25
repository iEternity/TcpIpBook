#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void errorHandling(const char* message);

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[1]);
        exit(1);
    }

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockServAddr;
    memset(&sockServAddr, 0, sizeof(sockServAddr));
    sockServAddr.sin_family = AF_INET;
    sockServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockServAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockServ, (struct sockaddr*)& sockServAddr, sizeof(sockServAddr)) ==-1){
        errorHandling("bind() error!");
    }

    if(listen(sockServ, 5) == -1){
        errorHandling("listen() error!");
    }

    struct sockaddr_in sockClientAddr;
    socklen_t clientAddrLen = sizeof(sockClientAddr);

    int sockClient = accept(sockServ, (struct sockaddr*)& sockClientAddr, &clientAddrLen);
    if(sockClient == -1){
        errorHandling("accept() error!");
    }
    else{
        puts("New Client connected...");
    }

    char message[] = "Hello World!";

    write(sockClient, message, strlen(message));

    close(sockClient);
    close(sockServ);

    return 0;
}

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}