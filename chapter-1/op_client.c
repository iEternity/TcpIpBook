#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
using namespace std;

void error_handling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[])
{
    if(argc!=3){
        printf("Usage:%s <ip> <port> \n",argv[0]);
        exit(1);
    }

    int clnt_sock = socket(PF_INET,SOCK_STREAM, 0);
    if(clnt_sock==-1){
        error_handling("socket() error");
    }

    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    serv_addr.sin_port          = htons(atoi(argv[2]));

    if(connect(clnt_sock,(sockaddr*)&serv_addr,sizeof(serv_addr)) == -1){
        error_handling("connect() error");
    }

    char message[64];
    int n;

    cout<<"please input operator number:"<<endl;
    cin>>n;
    message[0] = char(n);
    cout<<"please input "<<int(message[0])<<" of number:"<<endl;

    for(int i=0;i<(int)message[0];i++){
        scanf("%d",(int*)&message[4*i+1]);
        //cin>>message[4*i+1];
    }

    cout<<"please input operator(+ - * /):"<<endl;
    fgetc(stdin);
    scanf("%c",&message[4*n+1]);
    write(clnt_sock,message,4*n+2);
    close(clnt_sock);

    return 0;
}