#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void errorHandling(const char* message);

int main(int argc, char* argv[]){
    if(argc !=3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(-1 == connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandling("connect() error!");
    }
    else
        puts("Connect success!");
    
    char buf[32];
    while(1){
        if(NULL == fgets(buf, sizeof(buf), stdin)){
            errorHandling("gets() error!");
        }
        else{
            if((0 == strcmp(buf, "Q\n")) || (0 == strcmp(buf, "q\n"))){
                puts("Client disconnected...");
                break;
            }
            write(sock, buf, strlen(buf));
            int readLen = read(sock, buf, sizeof(buf)-1);
            buf[readLen] = 0;
            printf("Message from server: %s", buf);

            memset(buf, 0, sizeof(buf));
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