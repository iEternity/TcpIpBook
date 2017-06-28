#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main()
{
    const char string[] = "192.168.8.54";
    struct sockaddr_in sockAddr;

    if(inet_aton(string, &sockAddr.sin_addr)){
        printf("Network ordered integer address: %#x \n", sockAddr.sin_addr.s_addr);
    }
    else{
        errorHandling("inet_aton() error!");
    }
    return 0;
}