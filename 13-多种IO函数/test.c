#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    printf("sizeof(\"12345\"): %d \n", sizeof("12345"));
    printf("strlen(\"12345\"): %d \n", strlen("12345"));
    return 0;
}