# 标准I/O函数的优点
## 标准I/O函数的两个优点
- 标准I/O函数具有良好的移植性
- 标准I/O函数利用缓冲提高性能
## 标准I/O函数的几个缺点
- 不易进行双向通信
- 有时可能需要频繁的调用fflush函数
- 需要以FILE结构体指针的形式返回文件描述符
# 使用标准I/O函数
## 利用fdopen函数转换为FILE结构体指针
```
#include<stdio.h>
FILE* fdopen(int filedes, const char* mode);
//成功时返回FILE结构体指针，失败时返回NULL指针
```
- filedes:需要转换的文件描述符
- mode:将要创建的FILE结构体指针的模式信息
```
#include<stdio.h>
int fd = open("data.txt", O_WRONLY|O_CREATE|O_TRUNC);
FILE* fp = fdopen(fd, 'w');
fputs("Network c programming \n", fp);
fclose(fp);
```
## 利用fileno函数转换为文件描述符
```
#include<stdio.h>
int fileno(FILE* stream);
//成功时返回转换后的文件描述符，失败时返回-1
```