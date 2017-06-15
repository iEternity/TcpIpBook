#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 128

void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    int clnt_sock;
    sockaddr_in serv_addr;
    char message[BUF_SIZE];
    
    if(argc != 3){
        printf("Usage: %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }

    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(clnt_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    serv_addr.sin_port          = htons(atoi(argv[2]));

    if(connect(clnt_sock, (sockaddr*)&serv_addr,sizeof(serv_addr)) == -1){
        error_handling("connect() error");
    }
    else{
        printf("Connected...\n");
    }

    while(1){
        fputs("Input message(Q to quit): \n", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message,"q\n")||!strcmp(message, "Q\n")){
            break;
        }
        int write_len = write(clnt_sock, message, strlen(message));
        int read_len = 0, recv_len = 0;
        while(recv_len < write_len){
            read_len = read(clnt_sock, &message[recv_len], BUF_SIZE-1);
            if(read_len == -1){
                error_handling("read() error");
            }
            recv_len += read_len;
        }
        message[recv_len] = 0;
        printf("Message from server: %s", message);
    }
    close(clnt_sock);

    return 0;
}