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