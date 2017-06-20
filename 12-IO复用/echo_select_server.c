#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<string.h>

#define BUF_SIZE 32

void errorHandling(const char* message);

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    char buf[BUF_SIZE];
    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    fd_set readSet, cpyReadSet;
    FD_ZERO(&readSet);
    FD_SET(sockServ, &readSet);

    int fdMax = sockServ;
    
    timeval timeout;

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockServ, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        errorHandling("bind() error!");
    }

    if(listen(sockServ, 5) == -1){
        errorHandling("listen() error!");
    }

    while(1){
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        cpyReadSet = readSet;

        int fdNum = select(fdMax+1, &cpyReadSet, 0, 0, &timeout);
        if(fdNum == -1){
            break;
        }
        else if(fdNum == 0){
            continue;
        }
        else{
            for(int i=0;i<fdMax+1;i++){
                if(FD_ISSET(i, &cpyReadSet)){
                    if(i == sockServ){  //connection request
                        int sockClient = accept(sockServ, 0, 0);
                        if(sockClient == -1){
                            errorHandling("accept() error!");
                        }
                        else{
                            puts("New client connected...");

                            FD_SET(sockClient, &readSet);

                            if(fdMax < sockClient) fdMax = sockClient;


                        }
                    }
                    else{
                        int receivedBytes = read(i, buf, BUF_SIZE);
                        if(receivedBytes == 0){
                            FD_CLR(i, &readSet);
                            close(i);

                            puts("Client disconnected...");
                        }
                        else{
                            write(i, buf, receivedBytes);
                        }
                    } 
                }
            }
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