#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MAX_CLNT 256
#define BUF_SIZE 256

int clntSocks[MAX_CLNT];
int clntCount = 0;
pthread_mutex_t mutex;

void errorHandler(const char* message){
    perror(message);
    exit(1);
}

void sendMsg(char* buf, int len){
    pthread_mutex_lock(&mutex);
    for(int i=0;i<clntCount;i++){
        write(clntSocks[i], buf, len);
    }
    pthread_mutex_unlock(&mutex);
}

void* clntHandler(void* arg){
    int sock = *(int*)arg;
    int readLen = 0;
    char buf[BUF_SIZE];
    while(readLen = read(sock, buf, BUF_SIZE)){
        sendMsg(buf, readLen);
    }

    pthread_mutex_lock(&mutex);
    for(int i=0;i<clntCount;i++){
        if(clntSocks[i]==sock){
            int j = i;
            while(j<clntCount-1){
                clntSocks[i] = clntSocks[i+1];
                j++;
            }
            clntCount--;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    close(sock);
    return 0;
}

int main(int argc, char*argv[]){
    if(argc !=2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    int servSock = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(-1 == bind(servSock, (sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandler("bind error!");
    }

    if(-1 == listen(servSock, 5)){
        errorHandler("listen error!");
    }

    int clntSock;
    sockaddr_in clntAddr;
    socklen_t clntAddrLen = sizeof(clntAddr);
    pthread_t t_id;
    while(1){
        clntSock = accept(servSock, (sockaddr*)&clntAddr, &clntAddrLen);
        if(clntSock == -1){
            puts("accept error!");
            continue;
        }
        else{
            printf("Connected client ip: %s:%d \n", 
                    inet_ntoa(clntAddr.sin_addr), ntohs(clntAddr.sin_port));
        }

        pthread_mutex_lock(&mutex);
        clntSocks[clntCount++] = clntSock;
        pthread_mutex_unlock(&mutex);

        pthread_create(&t_id, NULL, clntHandler, (void*)&clntSock);
        pthread_detach(t_id);
    }

    pthread_mutex_destroy(&mutex);
    close(servSock);
    return 0;
}