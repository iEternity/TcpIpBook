#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    int sock_clnt;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    char message[1024];
    int str_len = 0;

    if(argc != 3){
        printf("Usage:%s <IP> <Port>\n", argv[0]);
    }

    sock_clnt = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_clnt == -1){
        error_handling("socket() error!");
    }

    memset(&clnt_addr, 0, sizeof(clnt_addr));
    clnt_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    clnt_addr.sin_family        = AF_INET;
    clnt_addr.sin_port          = htons(atoi(argv[2]));

    clnt_addr_size = sizeof(clnt_addr);
    if(connect(sock_clnt, (struct sockaddr*)&clnt_addr, clnt_addr_size) == -1){
        error_handling("connect() error!");
    }

    int index = 0,read_len = 0;
    /*while(read_len = read(sock_clnt, &message[index++], 1)){
        if(read_len == -1){
            error_handling("read() error");
        }
        str_len += read_len;
        printf("read_len: %d \n", read_len);
    }*/
    if(read(sock_clnt, message, 1023)==-1){
        error_handling("read() error");
    }
    //printf("Function read call count: %d \n", str_len);
    for(int i=0;i<3000;i++){
        printf("wait time %d \n", i);
    }
    printf("Message from server: %s\n", message);
    close(sock_clnt);
    return 0;
}