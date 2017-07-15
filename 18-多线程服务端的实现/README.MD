# 理解线程的概念
### 多进程模型的缺点
- 创建进程的过程会带来一定的开销
- 进程间完成数据交换需要用到特殊的IPC技术
- 进程的上下文切换带来巨大的开销
### 线程相比于进程具有如下的优点：
- 线程的创建和上下文的切换比进程的创建和上下文切换速度更快
- 线程间的数据交换不需要用到特殊的技术
### 进程和线程的差异
每个进程间的内存空间都是独立的，内存空间包括三个部分：数据区（保存全局变量）、堆区域（动态分配内存）、栈区域（函数运行时使用、局部变量）。<br>
多个线程间的静态数据区和堆区域是共享的，只有栈区域时独立的。这种方式可以获得如下优势：
- 上下文切换时不需要切换数据区和堆区域
- 可以通过数据区和堆交换数据
# 线程创建及运行
```
#include<pthread.h>
int pthread_create(
    pthread_t* restrict thread, const pthread_attr_t* restrict attr, 
    void* (*start_routine)(void*), void* restrict arg
);
//成功时返回0，失败时返回其他值
```
```
#include<pthread.h>
int pthread_join(pthread_t p_id, void** status);
//成功时返回0，失败时返回-1
```
# 线程同步
线程同步用于解决线程访问顺序引发的问题，需要同步的情况可以从如下两方面考虑：
- 同时访问同一内存空间时发生的情况
- 需要指定访问同一内存空间时线程的执行顺序的情况
## 互斥量
```
#include<pthread.h>
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_destroy(pthread_mutex_t* mutex);
//成功时返回0，失败时返回其他值
```
- mutex:保存互斥量的变量地址值
- attr:传递创建互斥量属性，没有特别需要指定的属性指定NULL
```
#include<pthread.h>
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```
## 信号量
```
#include<semaphore.h>
int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_destroy(sem_t* sem);
//成功时返回0，失败时返回其他值
```
- sem:保存信号量的变量地址值
- pshared:传递其他值时，创建多个进程共享的信号量，传递0时，创建只允许一个进程使用的信号量
- value:指定初始值

```
#include<semaphore.h>
int sem_post(sem_t* sem);
int sem_wait(sem_t* sem);
//成功时返回0，失败时返回其他值
```
- sem:传递给sem_post时信号量增加1，传递给sem_wait时信号量减少1

## pthread_detach
```
#include<pthread.h>
int pthread_detach(pthread_t thread);
//成功时返回0，失败时返回其他值
```
调用此函数后不能再调用pthread_join,调用该函数的线程不会阻塞，该函数引导线程结束之后销毁线程空间。