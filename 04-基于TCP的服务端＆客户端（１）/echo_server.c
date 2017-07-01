#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void errorHandling(const char* message);

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(-1 == bind(sockServ, (struct sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandling("bind() error!");
    }

    if(-1 == listen(sockServ, 5)){
        errorHandling("listen() error!");
    }

    char buf[32];
    for(int i=0;i<5;i++){
        int sockClient = accept(sockServ, 0, 0);

        if(-1 == sockClient) errorHandling("acept() error!");
        else puts("New client connected...");

        while(1){
            int readLen = read(sockClient, buf, sizeof(buf));
            if(readLen == 0){
                puts(" Client disconnected...");
                close(sockClient);
                break;
            }

           write(sockClient, buf, readLen);

        }
    }

    close(sockServ);

    return 0;
}

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}