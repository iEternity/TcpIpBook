#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/select.h>
#include<sys/time.h>

#define BUF_SIZE 32

int main()
{
    char buf[BUF_SIZE];

    fd_set readSet, tmpSet;
    FD_ZERO(&readSet);
    FD_SET(0, &readSet);

    struct timeval timeout;
    /*
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
    */

    while(1){
        tmpSet = readSet;

        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int result = select(1, &tmpSet, 0, 0, &timeout);
        if(result == -1)
        {
            puts("select() error!");
            break;
        }
        else if(result == 0){
            puts("time out!");
            //break;
        }
        else{
            if(FD_ISSET(0, &tmpSet)){
                int len = read(0, buf, BUF_SIZE);
                buf[len] = 0;

                printf("Message from consle %s", buf);
            }
        }
    }

    return 0;
}