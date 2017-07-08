# IP地址和域名之间的转换
## 利用域名获取IP地址
```
#include<netdb.h>
struct hostent* gethostbyname(const char* hostname);
//成功时返回hostent结构体指针，失败时返回NULL指针
```

```
struct hostent{
    char* h_name;       //官方域名
    char** h_aliases;   //别名列表
    int h_addrtype;     //ip地址类型
    int h_length;       //IP地址长度
    char** h_addr_list; //IP地址列表
}
```
```
#include<netdb.h>
struct hostent* gethostbyaddr(const char* addr, socklen_t len, int family);
//成功时返回hostent结构体的指针，失败时返回NULL指针
```