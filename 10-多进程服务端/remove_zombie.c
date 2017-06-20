#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void child_handler(int signo){
    if(signo == SIGCHLD){
        int status = 0;
        pid_t pid = waitpid(-1, &status, WNOHANG);

        if(WIFEXITED(status)){
            printf("child process pid: %d \n", pid);
            printf("child send: %d \n", WEXITSTATUS(status));
        }
    }
}

int main()
{
    struct sigaction act;
    act.sa_handler = child_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();

    if(pid == 0){
        puts("I'm child process");

        sleep(20);

        puts("child process will exit");
        exit(3);
    }
    else{
        printf("fork() child pid: %d \n", pid);
        puts("wait...");
        sleep(500);
    }

    return 0;
}
