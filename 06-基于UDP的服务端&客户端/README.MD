# 理解UDP
> 流控制是区分UDP和TCP最重要的标志；UDP并非每次都快于TCP，每次交换的数据量越大，TCP的传输速率越接近UDP的传输速率；TCP比UDP慢通常有以下两点原因：<br>
- 建立连接和连接断开的连接设置和清除过程；
- 收发数据的过程中为保证可靠性而增加的流控制机制
> 如果收发的数据量小但需要频繁建立连接时，UDP比TCP更快。

# 基于UDP的数据I/O函数
```
#include<sys/socket.h>
ssize_t sendto(int sock, void* buff, size_t nbytes, int flags,struct sockaddr* to, socklen_t addrlen);
//成功时返回发送的字节数，失败时返回-1
```
```
#include<sys/socket.h>
ssize_t recvfrom(int sock, void* buff, size_t nbytes, int flags, struct sockaddr* from socklen_t addrlen);
//成功时返回接收的字节数，失败时返回-1
```
# 创建已连接UDP套接字
通过sendto函数传输数据会经过以下三个步骤：<br>
- 向UDP套接字中注册目标IP和端口信息
- 传输数据
- 清除UDP套接字中注册的目标IP和端口信息
---
可以通过以下方式创建已连接UDP套接字，可以避免频繁的向UDP套接字中注册目标IP和端口信息。
```
int sock = socket(PF_INET, SOCK_DGRAM, 0);
struct sockaddr_in addr;
memset(&addr, 0, sizeof(addr));
addr.sin_family = ...
addr.sin_addr.s_addr = ...
addr.sin_port = ...
connect(sock, (struct sockaddr*)&addr, sizeof(addr));
```
以上创建的套接字方式与创建TCP客户端套接字的方式并无二致，但是此处的connect函数并没有与对方的UDP套接字连接，这里只是向sock中注册了目标IP和端口信息，之后收发数据就可以使用`write() read()`函数来进行收发数据。