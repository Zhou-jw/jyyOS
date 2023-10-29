#include "thread.h"
#include <string.h>
#define N 100000000

long sum = 0;
typedef int splock; //spinlock
splock spinlock = 0;
// 0: lock is available, 1: lock is held

int TestAndSet(splock *old_ptr, int new, char *s) {
    int old = *old_ptr; // fetch old value at old_ptr
    asm volatile(
    "lock xchgl %0, %1"
    : "+m"(*old_ptr), "=a"(old)
    : "1"(new)
    : "memory"
    );
    /*
    old = *old_ptr
    *old_ptr = new
    return old
    */
    return old; // return the old value
}

void lock(splock *lock, char *s) {
    while (TestAndSet(lock, 1, s) == 1); 
    // spin-wait (do nothing)
}

void unlock(splock *lock, char *s) {
    printf("%s:before lock is %d\n", s, *lock);
    *lock = 0;
    printf("%s:after lock is %d\n", s, *lock);
}

void Tsum1() {
  lock(&spinlock, "T1");
  for (int i = 0; i < N; i++) {
    sum++;
  }
  unlock(&spinlock, "T1");
}
void Tsum2() {
  lock(&spinlock, "T2");
  for (int i = 0; i < N; i++) {
    sum++;
  }
  unlock(&spinlock, "T2");
}
int main() {
  create(Tsum1);
  create(Tsum2);
  join();
  printf("sum = %ld\n", sum);
}