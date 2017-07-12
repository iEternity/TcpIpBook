# epoll理解及应用
## 基于select I/O复用技术速度慢的原因
- 调用select函数后针对所有监视的文件描述符循环遍历
- 每次调用select函数需要向操作系统传递所有的监视对象信息
## 实现epoll时必要的函数和结构体
### epoll_create
```
#include<sys/epoll.h>
int epoll_create(int size);
//成功时返回epoll文件描述符，失败时返回-1
```
- size:epoll实例的大小，在2.6.8版本以上的内核将完全忽略该参数
> epoll_create函数创建的资源与套接字相同，由操作系统管理。该函数返回的文件描述符主要用于区分不同的epoll实例。需要终止时，和其他文件描述符一样，需要调用close()函数。
### epoll_ctl
```
#include<sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
//成功时返回0，失败时返回-1
```
- epfd: epoll实例的文件描述符
- op：用于指定监视对象的添加，删除，更改等操作。
- fd：需要注册的监视对象文件描述符
- event:监视对象的事件类型
---
第二个参数传递的常量及含义如下：
- EPOLL_CTL_ADD:将文件描述符注册到epoll实例中
- EPOLL_CTL_DEL:将文件描述符从epoll中删除
- EPOLL_CTL_MOD:更改注册的文件描述符的关注事件发生情况
---
第四个参数的详细定义如下：
```
struct epoll_event{
    __uint32_t events;  //  事件类型
    epoll_data_t data;
}

typedef union epoll_data{
    void* ptr;
    int fd;
    __uint_32_t u32;
    __uint_64_t u64;
}epoll_data_t;
```
events事件类型：
- EPOLLIN:需要读取数据的情况
- EPOLLOUT：输出缓冲为空，可以立即发送数据
- EPOLLPRI:收到OOB（带外数据）的情况
- EPOLLRDHUP:断开连接或半关闭的情况，这在边缘出发方式下非常有用
- EPOLLERR:发生错误的情况
- EPOLLET:以边缘触发的方式得到事件通知
- EPOLLONESHOT:发生一次事件后，相应文件描述符不再收到事件通知。因此需要再次设置事件。
```
//epoll_ctl调用示例
struct epoll_event event;
event.events = EPOLLIN;
event.fd = sockfd;
epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
```
### epoll_wait
```
#include<sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
//成功时返回发生了事件的文件描述符的数量，失败时返回-1
```
- epfd:epoll实例的文件描述符
- events:表示发生事件的文件描述符集合的结构体地址
- maxevents:第二个参数中可以表示的最大的事件数
- timeout:以1毫秒为单位的等待时间，传递-1时，一直等待到发生事件
```
//代码示例
struct epoll_event* ep_events;
ep_events = malloc(sizeof(epoll_event)*EPOLL_SIZE);
int event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
```
# 水平触发和边缘触发
## 水平触发与边缘触发的区别在于发生事件的时间点
> 水平触发方式中，只要输入缓冲中有数据就会一直通知该事件。<br>
> 边缘触发方式中，输入缓冲区收到数据时只会通知一次事件，即使输入缓冲中还有未读取数据也不会再次通知。
## 边缘触发的服务端实现中必知的两点
- 通过errno变量验证错误的原因
- 更改套接字为非阻塞的方式
> 边缘触发方式中，接收数据时只会通知一次该事件，因此需要一次性将所有的数据读完。因此需要验证输入缓冲中是否为空。<br>
**read函数返回-1，变量`errno`中的值为`EAGAIN`时，说明没有数据可读。**<br>
为了访问`errno`变量需要包含`#include<errno.h>`。
---
> 在边缘触发方式中，如果套接字时阻塞方式工作，那么read&write函数有可能引起服务器的长时间停顿，因此在边缘触发方式中一定要将套接字更改为非阻塞的方式。
```
//更改文件属性函数
#include<fcntl.h>
int fcntl(int filedes, int cmd, ...);
```
```
//更改套接字为非阻塞方式
int flag = fcntl(fd, F_GETFL,0);
fcntl(fd, FSETFL, flag|O_NONBLOCK);
```
## 水平触发和边缘触发的优劣
边缘触发可以分离接收数据和处理数据的时间点，从实现模型的角度看边缘触发有可能带来高性能。