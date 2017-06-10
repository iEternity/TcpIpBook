#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
using namespace std;
#define BUF_SIZE 128

void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int calculate(int op_count, int num[],char ope){
    int result = 0;
    switch(ope)
    {
        case '+':
            for(int i=0;i<op_count;i++) result+=num[i];
        break;

        case '-':
            for(int i=0;i<op_count;i++) result-=num[i];
        break;

        case '*':
            for(int i=0;i<op_count;i++) result*=num[i];
        break;

        case '/':
            for(int i=0;i<op_count;i++) result/=num[i];
        break;

        default:break;
    }
    return result;
}

int main(int argc, char* argv[])
{
    int serv_sock,clnt_sock;
    sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    char buf[BUF_SIZE];

    if(argc!=2){
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

    if(bind(serv_sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }

    if(listen(serv_sock, 5) == -1){
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    while(1){
        clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1){
            error_handling("accept() error");
        }
        printf("op_client connected...\n");

        int op_count=0;
        read(clnt_sock, &op_count, 1);
        printf("op_count:%d\n",op_count);

        char num[64];
        char ope;
        int recv_len=0,recv_count=0;
        while(recv_len < sizeof(int)*op_count-1){
            recv_count = read(clnt_sock,&num[recv_len],63);
            if(recv_count == 0)break;
            printf("recv_count: %d\n",recv_count);
            recv_len+=recv_count;
        }
        //read(clnt_sock,&ope,1);
        for(int i=0;i<2;i++){
            cout<<(int*)num[i]<<endl;
        }
        int result = calculate(op_count,(int*)num,'+');
        printf("result: %d\n",result);
        close(clnt_sock);
        break;
    }

    close(serv_sock);
    return 0;
}