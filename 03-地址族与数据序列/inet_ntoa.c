#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
    struct in_addr addr;
    addr.s_addr = htonl(0x1020304);

    char* str = inet_ntoa(addr);

    char sockAddr[32];
    strcpy(sockAddr, str);

    printf("sockAddr: %s \n", sockAddr);
}