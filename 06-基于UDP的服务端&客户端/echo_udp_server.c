#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void errorHandler(const char* message){
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(atoi(argv[1]));

    if(-1 == bind(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr))){
        errorHandler("bind() error!");
    }

    struct sockaddr_in clntAddr;
    socklen_t clntAddrLen = sizeof(clntAddr);

    char buf[64];
    while(1){
        int recv_len = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&clntAddr, &clntAddrLen);
        sendto(sock, buf, recv_len, 0, (struct sockaddr*)& clntAddr, sizeof(clntAddr));
    }

    close(sock);
    return 0;
}