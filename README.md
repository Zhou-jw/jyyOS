## Lock
### Spinlock
#### Load and Store
[5/Alipay.c](5/alipay.c)

```c
typedef struct __lock_t { int flag; } lock_t;
void init(lock_t *mutex) {
    // 0 -> lock is available, 1 -> held
    mutex->flag = 0;
}
void lock(lock_t *mutex) {
   while (mutex->flag == 1); // TEST the flag; // spin-wait (do nothing)
    mutex->flag = 1; // now SET it!
}
void unlock(lock_t *mutex) {
   mutex->flag = 0;
}
```
```
Thread 1                            Thread 2
call lock()
while (flag == 1)
interrupt: switch to Thread 2
                                    call lock()
                                    while (flag == 1)
                                    flag = 1;
                                    interrupt: switch to Thread 1
flag = 1; // set flag to 1 (too!)
```

#### Test and Set
```
xchg(&lock, 1)
```
[7/Spinlock-test&set](7/Spinlock-test%26set.c)

#### Problem
- waste resources & time
##### Approch
1.
- yield() : give up the cpu and let other thread run.
 thread can be in three states(running , ready, blocked)
 yield() is a system call: thread(running -> ready)

```c
typedef struct __lock_t {
  int flag;
  int guard;
  queue_t* q;
} lock_t;
void lock_init(lock_t* m) {
  m->flag = 0;
  m->guard = 0;
  queue_init(m->q);
}

void lock(lock_t* m) {
  while (TestAndSet(&m->guard, 1) == 1)
    ; //acquire guard lock by spinning
  if (m->flag == 0) {
    m->flag = 1; // lock is acquired
    m->guard = 0;
  }
  else {
    queue_add(m->q, gettid());
    m->guard = 0;
    park(); // to put a calling thread to sleep
  }
}

void unlock(lock_t* m) {
  while (TestAndSet(&m->guard, 1) == 1)
    ; //acquire guard lock by spinning
  if (queue_empty(m->q))
    m->flag = 0; // let go of lock; no one wants it
  else
    unpark(queue_remove(m->q)); // hold lock
  // (for next thread!)
  //unpack(): wake a particular thread designated by threadID
  m->guard = 0;
}
```
but context switch is still costly
2.

## Sync
+lock(&mutex)
|
|   while(!cond)
|       wait(cv, mutex); //sleep() and release mutex, 
|                       //  wake up to acquire mutex again
|       // and check if satisfy cond the go on with mutex
|   assert(cond);
|   work();
|   
|   broadcast(cv)   //wake up all the threads that satisfy cond
+unlock(&mutex)

6.1810 / Fall 2022
https://pdos.csail.mit.edu/6.828/2022/schedule.html

操作系统：设计与实现 (2022 春季学期)
http://jyywiki.cn/OS/2022/

操作系统：设计与实现 (2023 春季学期)
http://jyywiki.cn/OS/2023/

Introduction · GitBook
https://nju-projectn.github.io/ics-pa-gitbook/ics2022/index.html

实验须知 - 操作系统2022秋 | 哈工大（深圳）
http://hitsz-cslab.gitee.io/os-labs/

Operating Systems: Three Easy Pieces
https://pages.cs.wisc.edu/~remzi/OSTEP/

操作系统-设计与实现-五 | H4wk1ns's blog
https://jiaweihawk.gitee.io/2021/09/07/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F-%E8%AE%BE%E8%AE%A1%E4%B8%8E%E5%AE%9E%E7%8E%B0-%E4%BA%94/

操作系统-设计与实现-四 | H4wk1ns's blog
https://jiaweihawk.gitee.io/2021/08/10/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F-%E8%AE%BE%E8%AE%A1%E4%B8%8E%E5%AE%9E%E7%8E%B0-%E5%9B%9B/

