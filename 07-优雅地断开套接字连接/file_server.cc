#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

    bind(sockServ, (sockaddr*)&addr, sizeof(addr));

    listen(sockServ, 5);

    char buf[32];
    while(1){
        int sockClient = accept(sockServ,0, 0);

        FILE* fp = fopen("test.txt", "rb");
        int readLen = 0;
        while(readLen = fread(buf, 1, sizeof(buf), fp)){
            write(sockClient, buf, readLen);
        }

        fclose(fp);
        shutdown(sockClient, SHUT_WR);

        readLen = read(sockClient, buf, sizeof(buf));
        buf[readLen] = 0;

        printf("Message from client: %s \n", buf);
        close(sockClient);
    }

    close(sockServ);

    return 0;
}