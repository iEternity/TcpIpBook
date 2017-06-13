#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>

#define BUF_SIZE 256

void errorHandling(const char* message);
void removeChildProc(int signo);

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
    }

    int fds[2];
    pipe(fds);

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = removeChildProc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();
    if(pid == 0){
        char buf[32];
        int fd = open("echo.txt", O_CREAT|O_APPEND|O_WRONLY, S_IRUSR|S_IWUSR);
        while(read(fds[0], buf, sizeof(buf))){
            write(fd, buf, strlen(buf));

            memset(buf, 0, sizeof(buf));
        }
        close(fd);

        return 0;
    }

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(bind(sockServ, (sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        errorHandling("bind() error!");
    }

    if(listen(sockServ, 5) != 0){
        errorHandling("listen() error!");
    }

    int sockClient;
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    char buf[BUF_SIZE];

    while(1){
        if((sockClient = accept(sockServ, (sockaddr*)&clientAddr, &clientAddrLen)) == -1){
            continue;
            //errorHandling("accept() error!");
        }
        else{
            puts("New client connected...");
        }

        pid_t pid = fork();
        if(pid == 0){
            close(sockServ);

            while(read(sockClient, buf, sizeof(buf)) !=0){
                printf("Message from client: %s", buf);

                buf[strlen(buf)] = 0;
                write(sockClient, buf, strlen(buf)+1);

                write(fds[1], buf, strlen(buf)+1);

                memset(buf, 0, BUF_SIZE);
            }

            close(sockClient);

            puts("Client disconnected...");
            
            return 0;
        }
        else{
            close(sockClient);
        }
    }

    close(sockServ);
    return 0;
}

void errorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}

void removeChildProc(int signo)
{
    if(signo == SIGCHLD){
        int status = 0;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        printf("remove child pid: %d \n", pid);
    }
}