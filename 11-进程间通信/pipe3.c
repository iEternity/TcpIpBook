#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    char str1[] = "who are you?";
    char str2[] = "Thank you for your message.";

    char buf[32];

    int fds1[2], fds2[2];

    pipe(fds1), pipe(fds2);

    pid_t pid = fork();
    if(pid == 0){
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, sizeof(buf));

        printf("child proc output: %s \n", buf);
    }
    else{
        read(fds1[0], buf, sizeof(buf));
        printf("parent proc output: %s\n", buf);
        
        write(fds2[1], str2, sizeof(str2));
    }

    return 0;
}