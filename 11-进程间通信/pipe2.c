#include<unistd.h>
#include<stdio.h>

int main ()
{
    int fds[2];

    pipe(fds);

    pid_t pid = fork();
    if(pid == 0){
        char str[] = "I'm from child proc";
        char buf[32];

        puts("child proc will write data");
        write(fds[1], str, sizeof(str));
        sleep(2);

        read(fds[0], buf, sizeof(buf));
        puts(buf);
    }
    else{
        char str[] = "I'm from parent proc";
        char buf[32];

        read(fds[0], buf, sizeof(buf));
        puts(buf);

        puts("parent will write data");
        write(fds[1], str, sizeof(str));
        sleep(2);
    }
    return 0;
}