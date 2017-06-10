# 通过调用fork函数创建进程
```
#include <unistd.h>

pid_t fork();//成功时返回进程ID，失败时返回-1
```
- 父进程：返回子进程ID <br>
- 子进程：返回0

# 销毁僵尸进程1：利用wait函数
```
#include <sys/wait.h>

pid_t wait(int* status);//成功时返回子进程ID，失败时返回-1
```
- `WIFEXITED(status)`: 子进程正常终止时返回true <br>
- `WEXITSTATUS(status)`: 返回子进程的返回值

# 销毁僵尸进程2：使用waitpid函数
```
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int* status, int option);
//成功时返回子进程ID或0,失败时返回-1
```
- pid: 目标子进程id，若传递-1,则与wait函数相同，可以等待任意子进程终止 <br>
- option: 传递常量WNOHANG，即使没有终止的子进程也不会进入阻塞状态，而是返回0并退出

# 信号与signal函数
```
#include <signal.h>

void (*signal(int signo, void(*func)(int)))(int);
```
- 函数名：signal <br>
- 参数：int signal, void(*func)(int) <br>
- 返回值：参数类型为int，返回值为void的函数指针 <br>

> 第一个参数表示特殊情况信息，第二个参数表示在该种特殊情况发生时所要调用的函数地址，下面给出部分可以在signal函数中注册的特殊情况和对应的常数。<br>

- `SIGALRM`:  已到通过调用`alarm()`函数注册的时间 
- `SIGINT`:   输入CTRL+C 
- `SIGCHILD`: 子进程终止 

```
#include <unistd.h>

unsigned int alarm(unsigned int seconds);
//返回0或以秒为单位距SIGALRM信号发生所剩时间
```
> 如果传递一个正整形参数，则经过相应时间后将产生一个SIGALRM信号。若传递0,则之前对SIGALRM信号的预约将取消。如果通过该函数预约信号后未指定对该信号的处理函数，则（通过调用`signal()`函数）终止进程，不做任何处理。 <br>

# 利用`SIGACTION`函数进行信号处理
```
#include <signal.h>

int sigaction(int signo, const struct sigaction* act, struct sigaction* oldact);
//成功时返回0,失败时返回-1
```

- signo:  与`signal`函数相同，传递信号信息
- act:    对应第一个参数的信号处理函数信息
- oldact: 通过此参数获取之前注册的处理信号的函数指针，若不需要则传递0

```
struct sigaction
{
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flag;
}
```
> 第一个参数用于指定信号的处理函数的地址，第二、三个参数用于指定信号相关的选项和特性，一般初始化为0即可。