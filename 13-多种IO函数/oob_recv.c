#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/select.h>
#include<fcntl.h>
#include<time.h>
#include<signal.h>

void errorHandling(const char* message);
void urgHandler(int signo);

int sockClient;

int main(int argc, char* argv[])
{
    if(argc!=2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = urgHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockServ, (sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        errorHandling("bind() error!");
    }

    if(listen(sockServ, 5) == -1){
        errorHandling("listen() error!");
    }

    sockClient = accept(sockServ, 0, 0);
    if(sockClient == -1){
        errorHandling("accept() error!");
    }
    else{
        fcntl(sockClient,F_SETOWN, getpid());
        sigaction(SIGURG, &act, 0);

        puts("New client connected...");
    }

    char buf[32];

    while(1){
        int readLen = recv(sockClient, buf, sizeof(buf), 0);
        if(readLen == -1) {
            puts("readLen == -1");
            continue;
        }
        else if(readLen == 0){
            puts("Client disconnected...");
            close(sockClient);
            break;
        }
        else{
            buf[readLen] = 0;
            puts(buf);
        }
    }

    close(sockServ);
    return 0;
}

void errorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void urgHandler(int signo)
{
    char buf[32];
    if(signo == SIGURG){
        int readLen = recv(sockClient, buf, sizeof(buf)-1, MSG_OOB);

        if(readLen == -1){
            puts("urgHandler() readLen == -1");
            return;
        }
        if(readLen == 0){
            puts("urgHandler() readLen == 0");
        }
        else{
            buf[readLen] = 0;
        
            printf("Urgent message: %s \n", buf);
        }
       
    }
}