#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define BUF_SIZE 128

void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[])
{   
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t serv_addr_size, clnt_addr_size;
    char buf[BUF_SIZE];

    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    serv_addr.sin_port          = htons(atoi(argv[1]));

    serv_addr_size = sizeof(serv_addr);
    if(bind(serv_sock,(sockaddr*)&serv_addr, serv_addr_size) == -1){
        error_handling("bind() error");
    }

    if(listen(serv_sock, 5) == -1){
        error_handling("listen() error");
    }

    for(int i=0;i<5;i++){
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1){
            error_handling("accept() error");
        }
        printf("Connect: %d...",i);
        while(1){
            int strlen = read(clnt_sock, buf, BUF_SIZE-1);
            if(strlen == -1){
                error_handling("read() error");
            }
            if(strlen == 0){
                break;
            }
            if(write(clnt_sock, buf, strlen) == -1){
                error_handling("write() error");
            }
        }
        close(clnt_sock);
    }
    close(serv_sock);
    


    return 0;
}