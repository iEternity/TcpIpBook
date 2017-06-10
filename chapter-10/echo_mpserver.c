#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>

#define BUFFSIZE 64

void errorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void removeChild(int signo)
{
    int status = 0;

    pid_t pid = waitpid(-1, &status, WNOHANG);
    
    printf("remove child process: pid = %d \n", pid);
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    struct sigaction act;
    act.sa_handler = removeChild;
    act.sa_flags   = 0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD,&act, 0);

    int sockServ, sockClnt;

    sockaddr_in addrServ, addrClnt;

    memset(&addrServ, 0, sizeof(addrServ));
    addrServ.sin_family         = AF_INET;
    addrServ.sin_addr.s_addr    = htonl(INADDR_ANY);
    addrServ.sin_port           = htons(atoi(argv[1]));         

    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    if(0 != bind(sockServ, (struct sockaddr*)&addrServ, sizeof(addrServ))){
        errorHandling("bind() error!");
    }

    if(0 != listen(sockServ, 5)){
        errorHandling("listen() error!");
    }

    socklen_t addrClntLen = sizeof(addrClnt);
    while(1){
        sockClnt = accept(sockServ, (struct sockaddr*)&addrClnt, &addrClntLen);
        if(sockClnt == -1){
            continue;
        }
        else{
            puts("new client connected...");
        }

        pid_t pid = fork();

        if(pid == -1){
            close(sockClnt);
            continue;
        }

        if(pid > 0){
            close(sockClnt);
        }
        else{
            close(sockServ);
            
            char buf[BUFFSIZE];
            int receivedByte = 0;
            while((receivedByte = read(sockClnt,buf, sizeof(buf)))>0){
                write(sockClnt, buf, receivedByte);
            }

            close(sockClnt);

            puts("client disconnected...");

            return 0;
        }
    }

    close(sockServ);
    return 0;
}