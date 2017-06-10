#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void timeout(int signo)
{
    if(signo == SIGALRM){
        puts("time out!");
    }
    alarm(2);
}

void ketcontrol(int signo)
{
    if(signo == SIGINT){
        puts("CTRL+C pressed!");
    }
}

int main(int argc, char* argv[])
{
    signal(SIGALRM, timeout);
    signal(SIGINT, ketcontrol);
    alarm(2);

    for(int i=0;i<3;i++){
        puts("wait...");
        sleep(100);
    }

    return 0;
}