# 第十一章　线程

## 线程中的函数
```
///判断两个线程ID是否相同
int pthread_equal(pthread_t tid1, pthread_t tid2)
///获取一个线程的ID值
int pthread_self(void)
///创建一个新线程
int pthread_create(pthread_t *tid, const pthread_attr_t *tid_attr, void *(*thread_fun)(void *), void * arg)
///终止线程
int pthread_exit(void *ptr)
///等待某个线程结束,二级指针为线程的返回值
int pthread_join(pthread_t thread, void **rtval_ptr)
```