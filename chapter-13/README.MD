# send & recv函数
```
#include<sys/socket.h>

ssize_t send(int sockfd, const void* buf, size_t nbytes, int flags);
//成功时返回发送的字节数，失败时返回-1

ssize_t recv(int sockfd, const void* buf, size_t nbytes, int flags);
//成功时返回接收到的字节数（收到EOF时返回0），失败时返回-1
```
> 这两个函数的最后一个参数是收发数据时的可选项，可以进行按位于'|'运算符进行指定多个选项，可选项及其含义如下：

 可选项(Option) | 含义    | send  | recv   
 ------|--------|-------|------
 
 