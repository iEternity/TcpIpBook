#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/uio.h>
#include<string.h>

int main()
{
    char buf1[] = "123456";
    char buf2[] = "abcdefg";

    struct iovec iov[2];
    iov[0].iov_base = buf1;
    iov[0].iov_len = strlen(buf1);
    iov[1].iov_base = buf2;
    iov[1].iov_len = strlen(buf2);

    int len = writev(1, iov, 2);
    puts("");
    printf("Write bytes: %d \n", len);

    return 0;
}