#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0){
        sleep(15);
        return 22;
    }
    else{
        int status = 0;

        while(!waitpid(-1, &status, WNOHANG)){
            sleep(3);
            printf("sleep 3 sec \n");
        }

        if(WIFEXITED(status)){
            printf("child send: %d \n",WEXITSTATUS(status));
        }

    }

    return 0;
}