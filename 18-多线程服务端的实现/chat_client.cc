#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>

#define BUF_SIZE 256
#define NAME_SIZE 16
char name[] ="[DEFAULT]";

void errorHandler(const char* message){
    perror(message);
    exit(1);
}

void* sendThread(void* arg){
    int sock = *(int*)arg;
    char buf[BUF_SIZE];
    char msg[NAME_SIZE+BUF_SIZE];
    while(fgets(buf, BUF_SIZE, stdin)){
        if(!strcmp(buf, "Q\n") || !strcmp(buf, "q\n")){
            close(sock);
            exit(0);
        }
        sprintf(msg, "%s %s", name, buf);
        write(sock, msg, NAME_SIZE+BUF_SIZE);
    }
    return 0;
}

void* receiveThread(void* arg){
    int sock = *(int*)arg;
    char msg[BUF_SIZE+NAME_SIZE];
    int recvLen;
    while(1){
        recvLen = read(sock, msg, NAME_SIZE+BUF_SIZE-1);
        if(recvLen == -1){
            break;
        }
        msg[recvLen] = 0;
        fputs(msg, stdout);
    }
    return 0;
}

int main(int argc, char* argv[]){
    if(argc != 4){
        printf("Usage: %s <ip> <port> <name> \n", argv[0]);
        exit(1);
    }
    sprintf(name, "[%s]", argv[3]);
    int sock = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(-1 == connect(sock, (sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandler("connect error!");
    }

    pthread_t t_id[2];
    pthread_create(&t_id[0], NULL, sendThread, (void*)&sock);
    pthread_create(&t_id[1], NULL, receiveThread, (void*)&sock);
    pthread_join(t_id[0], NULL);
    pthread_join(t_id[1], NULL);

    close(sock);
    return 0;
}