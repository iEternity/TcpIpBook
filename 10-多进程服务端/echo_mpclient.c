#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>

#define BUF_SIZE 64

void errorHandling(const char*);
void readRoutine(int fd);
void writeRoutine(int fd);
void removeChildProc(int signo);

int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = removeChildProc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, 0);

    int sockClnt = socket(PF_INET, SOCK_STREAM, 0);
    if(sockClnt == -1){
        errorHandling("sockt() error!");
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    socklen_t servAddrLen = sizeof(servAddr);
    if(connect(sockClnt, (struct sockaddr*)&servAddr, servAddrLen) == -1){
        errorHandling("connect() error!");
    }

    pid_t pid = fork();
    if(pid == 0){
        writeRoutine(sockClnt);
        return 0;
    }
    else{
        readRoutine(sockClnt);
    }

    close(sockClnt);
    sleep(10);
    return 0;
}

void errorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}

void readRoutine(int fd)
{
    char buf[BUF_SIZE];
    int receivedBytes = 0;
    while(receivedBytes = read(fd, buf, sizeof(buf))){
        printf("Message from server: %s ", buf);
        memset(buf, 0, sizeof(buf));
    }

}

void writeRoutine(int fd)
{
    char buf[BUF_SIZE];
    while(1){
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf)+1] = 0;
        if(!strcmp(buf,"Q\n") || !strcmp(buf, "q\n")){
            shutdown(fd, SHUT_WR);
            return ;
        }
        else{
            write(fd, buf, strlen(buf));
        }
    }
}

void removeChildProc(int signo)
{
    printf("removeChildProc() signo: %d \n", signo);
    if(signo == SIGCHLD){
        int status = 0;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        printf("Remove child proc pid: %d \n", pid);
    }
}