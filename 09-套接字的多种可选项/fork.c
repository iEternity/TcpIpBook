#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int gVal = 10;

int main()
{
    int lVal = 20;

    pid_t pid = fork();

    if(pid == 0){
        lVal++;
    }
    else{
        gVal++;
    }

    if(pid == 0){
        printf("Child Proc: [%d, %d]\n", gVal, lVal);
    }
    else
        printf("Parent Proc: [%d, %d]\n", gVal, lVal);

    return 0;
}