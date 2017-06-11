# 通过管道实现进程间通信
```
#include<unistd.h>

int pipe(int filedes[2]);
//成功时返回0，失败时返回-1
```

- filedes[0]: 通过管道接收数据时使用的文件描述符，即管道出口
- filedes[1]: 通过管道发送数据时使用的文件描述符，即管道入口
