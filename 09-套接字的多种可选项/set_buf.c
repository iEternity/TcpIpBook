#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}

void main()
{
    int sock;
    int send_buf,recv_buf,state;
    socklen_t buf_len;

    buf_len = sizeof(send_buf);
    sock = socket(PF_INET, SOCK_STREAM, 0);

    send_buf = 1024*3;
    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &send_buf, buf_len);
    if(state)
        error_handling("setsockopt() error!");

    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &send_buf, &buf_len);
    if(state)
        error_handling("getsockopt() error!");
    printf("SO_SNDBUF: %d \n", send_buf);

    sock = socket(PF_INET, SOCK_STREAM, 0);

    recv_buf = 1024*3;
    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recv_buf, buf_len);
    if(state)
        error_handling("setsockopt() error!");

    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recv_buf, &buf_len);
    if(state)
        error_handling("getsockopt() error!");
    printf("SO_RCVBUF: %d \n", recv_buf);    
    
}