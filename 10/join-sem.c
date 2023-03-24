#include "thread.h"
#include "thread-sync.h"

#define T 4
#define N 10000000

sem_t done;
long sum = 0;

void atomic_inc(long *ptr) {
  asm volatile(
    "lock incq %0"
    : "+m"(*ptr) : : "memory"
  );
}

void Tsum() {
  for (int i = 0; i < N; i++) {
    atomic_inc(&sum);
  }
  V(&done); //对 done 这个信号量 +1
}

void Tprint() { //另一个线程
  for (int i = 0; i < T-1; i++) {
    P(&done);
  }
  printf("sum = %ld\n", sum);
}

int main() {
  SEM_INIT(&done, 0);
  for (int i = 0; i < T; i++) {
    create(Tsum);
  }
  create(Tprint);
}