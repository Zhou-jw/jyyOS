#include "../thread.h"

#define N 10000

long sum = 0;

void Tsum() {
  for (int i = 0; i < N; i++) {
    asm volatile("lock addq $1, %0": "+m"(sum));
  }
}

int main() {
  for(int i=0; i<=10; i++) {
    create(Tsum);
  }
  join();
  for(int j = 0; j<=7; j++) {
    for(int i=0; i<=10; i++) {
      create(Tsum);
    }
    join();
  }
  printf("sum = %ld\n", sum);
}
