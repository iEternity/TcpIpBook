#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void errorHandling(const char* message);

int main(int argc, char* argv[])
{
    if(argc!=3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    struct ip_mreq joinAddr;
    joinAddr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    joinAddr.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&joinAddr, sizeof(joinAddr));

    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(atoi(argv[2]));

    if(bind(sock, (struct sockaddr*)& sockAddr, sizeof(sockAddr)) == -1){
        errorHandling("bind() error!");
    }

    char buf[256];
    while(1){
        int readLen = recvfrom(sock, buf, sizeof(buf)-1, 0, 0, 0);

        if(readLen >0){
            buf[readLen] = 0;

            fputs(buf, stdout);
        }
        else{
            break;
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