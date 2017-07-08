#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>

void errorHandler(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <ip> \n", argv[0]);
        exit(1);
    }

    hostent* host = gethostbyaddr(argv[1], 4, AF_INET);
    if(!host){
        errorHandler("gethostbyaddr() error!");
    }

    printf("Official name: %s \n", host->h_name);
    for(int i=0;host->h_aliases[i];i++){
        printf("Aliases %d: %s\n", i+1, host->h_aliases[i]);
    }
    printf("Address type: %s \n", host->h_addrtype == AF_INET? "AF_INET":"AF_INET6");
    for(int i=0;host->h_addr_list[i];i++){
        printf("IP address %d: %s \n", i+1, inet_ntoa(*(in_addr*)host->h_addr_list[i]));
    }

    return 0;
}