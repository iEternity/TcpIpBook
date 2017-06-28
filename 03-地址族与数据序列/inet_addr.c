#include<stdio.h>
#include<arpa/inet.h>

int main(){
    const char* addr1 = "192.168.8.54";
    const char* addr2 = "192.168.8.256";

    unsigned int convAddr = inet_addr(addr1);
    if(convAddr == INADDR_NONE){
        puts("Error occured!");
    }
    else{
        printf("Network ordered integer addr: %#x \n", convAddr);
    }

    convAddr = inet_addr(addr2);
    if(convAddr == INADDR_NONE){
        printf("Error occured! \n");
    }
    else
        printf("Network ordered integer addr: %#x \n", convAddr);

    return 0;
}