#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>

int main(){
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("host port: %#x \n", host_port);
    printf("net port: %#x \n", net_port);
    printf("host ip: %#lx \n", host_addr);
    printf("net ip: %#lx \n", net_addr);

    return 0;
}