#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void errorHandling(const char* message);

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(-1 == connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandling("connect() error!");
    }
    else
        puts("Connect Success!");
    
    char buf[1024];
    while(1){
        puts("Input message('Q' or 'q' to quit!)");

        fgets(buf, sizeof(buf), stdin);

        if(!strcmp(buf, "Q") || !strcmp(buf, "q")){
            break;
        }

        int writeLen = write(sock, buf, strlen(buf));

        int readLen = 0;
        while(readLen < writeLen){
            int bytes = read(sock, &buf[readLen], sizeof(buf)-readLen-1);

            if(bytes == -1){
                errorHandling("read() error!");
            }
            readLen += bytes;
        }

        buf[readLen] = 0;
        printf("Message from server: %s", buf);
    }

    close(sock);
    return 0;
}

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}