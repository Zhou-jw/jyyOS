#include <unistd.h>
#include <stdio.h>

int main() {
  // 128MB of padding NOP
  asm volatile(
    ".fill (128 << 20), 1, 0x90"
  );

  // Print the process ID
  printf("pid = %d\n", getpid());
  while (1) {
    sleep(1);
  }
}