# 复制文件描述符
```
#include<unistd.h>
int dup(int filedes);
int dup2(int filedes, int filedes2);
//成功返回复制后的文件描述符，失败时返回-1
```
- filedes:需要复制的文件描述符
- filedes2:明确指定的文件描述符整数值