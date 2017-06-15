# 设置文件描述符
- `FD_ZERO(fd_set* fdset)`: 将fdset变量的所有位初始化位0
- `FD_SET(int fd, fd_set* fdset)`: 向fdset变量中注册文件描述符fd
- `FD_CLR(int fd, fd_set* fdset)`: 清除fdset变量中的文件描述符fd
- `FD_ISSET(int fd, fd_set* fdset)`: fdset变量中是否存在fd文件描述符

# 设置监视范围及超时
```
#include<sys/select.h>
#include<sys/time.h>

int select(int maxfd, fd_set* readset, 
            fd_set* writeset,fd_set* exceptset, 
            const struct timeval* timeout
            );
//失败时返回-1，超时返回0，成功时返回发生事件的文件描述符数量

struct timeval
{
    long tv_sec;
    long tv_usec;
}
```
- maxfd: 监视的文件描述符数量（最大的文件描述符+1）
- readset: 将关注“是否存在待读取数据”的文件描述符存放在readset变量中
- writeset: 将关注”是否可写“的文件描述符存放在writeset变量中
- exceptset: 将关注”是否有异常“的文件描述符放在exceptset变量中
-timeout: 为了防止调用select函数后陷入无限阻塞状态，可以传递超时信息
