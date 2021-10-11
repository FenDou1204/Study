# 锁的用法


## 知识点

## 互斥锁

### 概念
互斥锁应用于多任务系统。假如同时运行多个任务需要同一个资源，多个任务交叉执行就会出现错误。互斥锁是一种简单的加锁方法来控制对共享资源的访问。互斥锁有两种状态:加锁于解锁。

### 特点
- 原子性 一个互斥量为一个原子操作，
- 唯一性 如果一个线程锁定了互斥量，其他所有线程都不能锁定此互斥量
- 非繁忙等待 如果一个互斥量已经被锁定，后续的线程去锁定互斥量，则此线程被挂起，直到互斥量被解锁，后续线程才可以锁定互斥量继续执行

### 操作流程
- 初始化锁
- 在访问共享资源之前，对于互斥锁进行锁定
- 访问结束后，对互斥量进行解锁
- 其他线程进行类似操作
- 销毁锁

### 互斥锁中的函数

```
    ///初始化锁,第二个传参设置为线程属性
    int pthread_mutex_init(pthread_mutex_t *mutex,
                           const pthread_mutexattr_t *attr)
    ///销毁锁，使用完锁后必须进行销毁
    int pthread_mutex_destroy(pthread_mutex_t *mutex)
    ///对互斥锁上锁，若互斥锁已经上锁，则一直处于阻塞，直到解锁后再上锁
    int pthread_mutex_lock(pthread_mutex_t *mutex)
    ///对于互斥锁解锁
    int pthread_mutex_unlock(pthread_mutex_t *mutex)
    ///如果互斥锁未加锁，则加锁，返回值为0；如果已经加锁，返回值为EBUSY
    int pthread_mutex_trylock(pthread_mutex_t *mutex)
    ///
    int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *time_out)
```    

## 条件变量

### 概念
条件变量是用来等待而不是用来上锁。条件变量用来自动阻塞一个线程，知道某种特殊情况发生为止。**通常和互斥锁一同使用**。

### 原理
条件检测实在互斥锁保护下进行的。线程在改变条件状态之前必须首先锁住互斥量。如果一个条件为假，一个线程自动阻塞，释放等待状态的锁；如果另一个线程改变了条件，发信号给关联的条件变量，唤醒多个等待它的线程，重新获取互斥锁，重新评价条件。如果两进程共享可读写内存，条件变量可以被用来实现进程间的线程同步。

### 使用流程
1. 初始化条件变量
2. 等待条件成立
3. 激活条件变量
4. 清除条件变量

###　涉及函数
```
///初始化条件变量，一般属性置为NULL即可
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr)
///销毁条件变量，释放资源
int pthread_cond_destroy(pthread_cond_t *cond)
///阻塞等待条件变量符合。此函数一旦进入wait状态就会自动释放锁，一旦条件满足线程锁会自动上锁
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
///超时等待
int pthread_cond_timewait(pthread_cond_t *cond, pthread_mutex_t *mutex)
///至少唤醒一个等待该条件线程
int pthread_cond_signal(pthread_cond_t *cond)
///唤醒所有等待该条件的线程
int pthread_cond_broadcase(pthread_cond_t *cond)
```

## 读写锁
读写锁也叫共享互斥锁。读写锁允许更改并行性。
读写锁有3种状态:读模式加锁，写模式加锁，不加锁状态。
### 特点
- 一次只能有一个线程占有写模式读写锁，但是可以有多个线程占有读模式读写锁
- 如果其他线程读数据，允许其他线程进行读操作，但不允许写操作
- 如果有线程写数据，则其他线程不允许读写操作

### 使用情况
- **一个线程申请读锁，其他线程可以申请读锁，不能申请写锁**
- **一个线程申请写锁，其他线程不可以读不可以写**
- **读写锁适合于对于数据机构读次数比写次数多的多的情况**

### 涉及函数
```
///初始化读写锁
int pthread_rwlock_init(pthread_rwlock_t *rwlock,
const pthread_rwlockattr_t *attr)
///销毁读写锁
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
///申请读锁
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
///申请写锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
///尝试申请写锁
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
///解锁
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
```

## 自旋锁
自旋锁与互斥量功能一样，唯一一点不同的就是互斥量阻塞后休眠让出cpu，而自旋锁阻塞后不会让出cpu，会一直忙等待，直到得到锁。
**自旋锁在用户态使用的比较少，在内核使用的比较多**自旋锁的使用场景：锁的持有时间比较短，或者说小于2次上下文切换的时间。
自旋锁在用户态的函数接口和互斥量一样，把pthread_mutex_xxx()中mutex换成spin，如：pthread_spin_init()。

## 信号量
信号量用于进程或线程间的同步和互斥，信号量本质上是一个非负的整数计数器，被用来控制对公共资源的访问。

编程时可根据操作信号量值的结果判断是否对公共资源具有访问的权限，当信号量值大于 0 时，则可以访问，否则将阻塞。PV 原语是对信号量的操作，一次 P 操作使信号量减１，一次 V 操作使信号量加１。

### 信号量函数
```
///包含的头文件不是pthread系列的
#include <semaphore.h>
///初始化一个信号量
int sem_init(sem_t *sem, int pshared, unsigned int value)
///销毁一个信号量
int sem_destroy(sem_t *sem)
///信号量Ｐ操作(-1)
int sem_wait(sem_t *sem)
///非阻塞方式信号量P操作(-1)
int sem_trywait(sem_t *sem)
///信号量Ｖ操作(+1)
int sem_post(sem_t *sem)
///获取当前的信号量
int sem_getvalue(sem_t *sem, int *sval)

```
## 参考文档
[https://blog.csdn.net/daaikuaichuan/article/details/82950711](https://blog.csdn.net/daaikuaichuan/article/details/82950711)