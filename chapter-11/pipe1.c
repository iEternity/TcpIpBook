#include<unistd.h>
#include<stdio.h>

int main()
{
    int filedes[2];
    pipe(filedes);

    char str[] = "who are you?";

    pid_t pid = fork();
    if(pid == 0){
        puts("child will write data");
        write(filedes[1], str, sizeof(str));
    }
    else{
        char buf[32];
        puts("parent will read data");
        read(filedes[0], buf, sizeof(buf));
        puts(buf);
    }

    return 0;
}