# 理解网络编程和套接字
## 构建套接字
```
#include<sys/socket.h>

int socket(int domain, int type, int protocol);
//成功时返回文件描述符，失败时返回-1
```
## 分配地址信息
```
#include<sys/socket.h>
int bind(int sockfd, struct sockaddr* pSockAddr, socklen_t addrLen);
//成功时返回0， 失败时返回-1
```
## 设置监听
```
#include<sys/socket.h>

int listen(int sockfd, int backlog);
//成功时返回0， 失败时返回-1
```
## 受理连接
```
#include<sys/socket.h>

int accept(int sockfd, struct sockaddr* pSockAddr, socklen_t* pAddrLen);
//成功时返回文件描述符，失败时返回-1
```

## 请求连接
```
#include<sys/socket.h>

int connect(in sockfd, struct sockaddr* pSockAddr, socklen_t sockLen);
//成功时返回0， 失败时返回-1
```

# 基于Linux的文件操作
## 系统文件描述符
文件描述符  |对象
:--------:|:----:
0         |标准输入：stdin
1         |标准输出：stdout
2         |标准错误：stderr

## 打开文件
```
#include<fcntl.h>

int open(const char* path, int flag);
//成功时返回文件描述符， 失败时返回-1
```
- path: 文件路径
- flag: 文件打开模式信息

### 文件打开模式如下表：
---
打开模式    |含义
:---------:|:---:
O_CREAT    |必要时创建文件
O_TRUNC    |删除全部现有数据
O_APPEND   |维持现有数据，追加到后面
O_RDONLY   |以只读方式打开
O_WRONLY   |以只写方式打开
O_RDWR     |以读写方式打开

## 关闭文件
```
#include<unistd.h>

int close(int fd);
//成功时返回0， 失败时返回-1
```
## 将数据写入文件
```
#include<unistd.h>

ssize_t write(int fd, const void* buf, size_t nBytes);
//成功时返回写入的字节数，失败时返回-1
```
## 读取文件中的数据
```
#include<unistd.h>

ssize_t read(int fd, void* buf, size_t nBytes);
//成功时返回读到的字节数（若遇到文件结尾则返回0），失败时返回-1
```
