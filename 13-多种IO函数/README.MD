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
 :------:|:--------:|:-------:|:------:
 MSG_OOB|用于传输带外的数据（out-of-band data)|Y|Y
 MSG_PEEK|验证输入缓冲中是否存在接收的数据|N|Y
 MSG_DONTROUTE|数据传输过程中不参照路由表，在本地网络中寻找目的地|Y|N
 MSG_DONTWAIT|调用IO函数时不阻塞|Y|Y
 MSG_WAITALL|防止函数返回，直到接收请求的全部的字节数|N|Y

# fcntl函数
```
#include<fcntl.h>

fcntl(sockRecv, F_SETOWN, getpid());
```
> 上述函数调用的作用是：将文件描述符`sockRecv`指向的拥有者改为`getpid()`函数返回的ID的进程；处理SIGURG信号时必须指定处理信号的进程.

# 检查输入缓冲
> `MSG_PEEK`和`MSG_DONTWAIT`同时使用时可以用来检查输入缓冲区是否有待接收的数据，并且不会删除这些数据.

# readv & writev函数
```
#include<sys/uio.h>

ssize_t writev(int filedes, const struct iovec* iov, int iovcnt);
//成功时返回发送的字节数，失败时返回-1

ssizea_t readv(int filedes, const struct iovec* iov, int iovcnt);
```
- filedes:文件描述符
- iov:iovec结构体数组的首地址
- iovcnt:第二个参数数组的长度

```
struct iovec
{
    void* iov_base; //缓冲地址
    size_t iov_len; //缓冲大小
}
```