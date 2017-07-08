# 套接字的可选项和IO缓冲大小
## getsockopt & setsockopt
```
#include<sys/socket.h>
int getsockopt(int sock, int level, int optname,void* optval,socklen_t* optlen);
//成功时返回0，失败时返回-1
```
- sock:套接字文件描述符
- level:要查看的协议层
- optname:要查看的可选项名
- optval:保存查看结果的缓冲地址值
- optlen:第四个参数的缓冲大小

```
#include<sys/socket.h>
int setsockopt(int sock, int level, int optname, void*optval,socklen_t optlen);
//成功时返回0，失败时返回-1
```
## SO_SNDBUF & SO_RCVBUF
```
int sock = socket(PF_INET,SOCK_STREAM,0);
int optval;
socklen_t optlen;
int state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF,(void*)&optval, &optlen);

optval = 1024*3;
optlen = sizeof(optval);
state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF,(void*)&optval,optlen);
```
## 地址再分配
```
int sock = socket(PF_INET, SOCK_STREAM, 0);
int optval = 1;
socklen_t optlen = sizeof(optval);
int state = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,(void*)&optval, optlen);
```

## TCP_NODELAY
```
int sock = socket(PF_INET, SOCK_STREAM, 0);
int optval =1;
int state = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(void*)&optval,sizeof(optval));
```