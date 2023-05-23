#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>

#define STRINGIFY(s) #s
#define TOSTRING(s)  STRINGIFY(s)

void padding() {
  asm volatile(
    ".fill " TOSTRING(PADDING) ", 1, 0x90"
  );
}

__attribute__((noinline)) void foo() {
  printf("In old function %s\n", __func__);
}

__attribute__((noinline)) void foo_new() {
  printf("In new function %s\n", __func__);
}

// 48 b8 (64-bit imm)   movabs $imm,%rax
// ff e0                jmpq   *%rax
const char PATCH[] = "\x48\xb8--------\xff\xe0";

void DSU(void *func, void *func_new) {
  int flag = PROT_WRITE | PROT_READ | PROT_EXEC, rc, np;

  // Grant write permission to the memory
  // We must handle boundary cases
  uintptr_t fn = (uintptr_t)func;
  uintptr_t base = fn & ~0xfff;
  if (fn + sizeof(PATCH) > base + 4096) { //按照4kb对齐，计算当前有没有超过页边界
    np = 2; //超过就要2页可写
  } else {
    np = 1; //没超过1页就行
  }
  printf("np = %d\n", np);

  rc = mprotect((void *)base, np * 4096, flag); // return code
  assert(rc == 0);  // Not expecting a failure
  
  // Patch the first instruction (this is UB in C spec)
  memcpy(func, PATCH, sizeof(PATCH));
  memcpy((char *)func + 2, &func_new, sizeof(func_new));

  // Revoke the write permission
  rc = mprotect((void *)base, np * 4096, PROT_READ | PROT_EXEC);
  assert(rc == 0);  // Not expecting a failure
}

int main() {
  setbuf(stdout, NULL);
  foo();
  DSU(foo, foo_new);  // Dynamic software update
  foo();
}
// gcc -DPADDING=0 -g -Wall dsu.c
