#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(const char* message);

int main(int argc, char* argv[])
{
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);

    printf("SOCK_STREAM: %d \n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d \n", SOCK_DGRAM);

    int state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, &sock_type, &socklen);
    if(state)
        error_handling("getsockopt error!");
    
    printf("sock_type: %d \n", sock_type);
    
    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, &sock_type, &socklen);
    if(state)
        error_handling("getsockopt error!");
    
    printf("sock_type: %d \n", sock_type);

    return 0;
}

void error_handling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}