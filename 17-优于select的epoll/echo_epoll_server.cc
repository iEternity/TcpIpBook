#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 64

void errorHandler(const char* message){
    perror(message);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(-1 == bind(sockServ, (sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandler("bind error!");
    }

    if(-1 == listen(sockServ, 5)){
        errorHandler("listen error!");
    }

    int epfd = epoll_create(EPOLL_SIZE);

    epoll_event event;
    event.data.fd = sockServ;
    event.events = EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, sockServ, &event);

    epoll_event* pEvents;
    pEvents = (epoll_event*)malloc(sizeof(epoll_event)*EPOLL_SIZE);

    int eventCount;
    char buf[BUF_SIZE];
    int sockClient;
    int readLen;

    while(1){
        eventCount = epoll_wait(epfd, pEvents, EPOLL_SIZE, -1);
        puts("epoll_wait...");

        for(int i=0;i<eventCount;i++){
            if(pEvents[i].data.fd == sockServ){ // client connected...
                sockClient = accept(sockServ,0,0);
                printf("Client %d connected...\n", sockClient);

                event.data.fd = sockClient;
                event.events = EPOLLIN;

                epoll_ctl(epfd, EPOLL_CTL_ADD, sockClient, &event);
            }
            else{
                readLen = read(pEvents[i].data.fd, buf, BUF_SIZE);
                if(readLen == 0){   //client disconnected...
                    epoll_ctl(epfd, EPOLL_CTL_DEL, pEvents[i].data.fd, NULL);
                    close(pEvents[i].data.fd);
                }
                else{
                    write(pEvents[i].data.fd, buf, readLen);
                }
            }
        }
    }

    close(sockServ);
    close(epfd);
    return 0;
}