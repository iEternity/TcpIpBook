# 分配给套接字的IP地址与端口号
## 网络地址
- IPv4:4字节地址
- IPv6:16字节地址

- A类网络地址首字节范围：0~127
- B类网络地址首字节范围：128~191
- C类网络地址首字节范围：192~223

# 地址信息的表示
## 表示IPv4地址的结构体
```
struct sockaddr_in
{
    sa_family_t sin_family; //地址族
    uint16_t sin_port;      //16位端口号
    struct in_addr sin_addr;//32位IP地址
    char zero[8];           //不使用
}

struct in_addr
{
    in_addr_t s_addr;   //32位IP地址
}

struct sockaddr
{
    sa_family_t sin_family;
    char sa_data[14];
}
```

# 网络字节序列与地址转换
## 字节序与网络字节序列
- 大端序（Big Endian）：低位地址存储高位字节
- 小端序(Little Endian)：高位地址存储高位字节
- 网络字节序列(Network Byte Order)：统一为大端序
## 字节序列转换(Endian Conversions)
```
unsigned short htons(unsigned short);    //主机字节序->网络字节序
unsigned short ntohs(unsigned short);    //网络字节序列->主机字节序列
unsigned long htonl(unsigned long);      
unsigned long ntohl(unsigned long);
```
# 网络地址的初始化与分配
## 将字符串信息转换为网络字节序列的整数型
```
#include<arpa/inet.h>

in_addr_t inet_addr(const char* string);
//成功时返回32位大端序列整型数值，失败时返回INADDR_NONE

int inet_aton(const char* string, struct in_addr* addr);
//成功时返回true，失败时返回false

char* inet_ntoa(struct in_addr addr);
```