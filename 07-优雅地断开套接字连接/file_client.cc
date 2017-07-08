#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char*argv[]){
    if(argc!=3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    connect(sock, (sockaddr*)&servAddr, sizeof(servAddr));

    FILE* fp = fopen("receive.txt", "wb");
    char buf[32];

    int readLen = 0;
    while(readLen = read(sock, buf, sizeof(buf))){
        fwrite(buf,1, readLen, fp);
    }

    fclose(fp);
    write(sock, "Thank you!", strlen("Thank you!"));
    close(sock);
}