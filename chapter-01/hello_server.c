#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

char message[] = "Hello World!";
void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in servAddr, clntAddr;
    socklen_t clntAddrSize;

    if(argc!=2){
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handling("socket() error!");
    }

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_addr.s_addr    = htonl(INADDR_ANY);
    servAddr.sin_family         = AF_INET;
    servAddr.sin_port           = htons(atoi(argv[1]));

    if(bind(serv_sock,  (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        error_handling("bind() error!");
    }
    
    if(listen(serv_sock,5) == -1){
        error_handling("listen() error!");
    }

    clntAddrSize = sizeof(clntAddr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clntAddr,&clntAddrSize);
    if(clnt_sock == -1){
        error_handling("accept() error!");
    }

    for(int i=0;i<5;i++){
        write(clnt_sock, message, sizeof(message));
    }
    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}