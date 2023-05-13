// By GPT-4

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void* malloc(size_t size) {
  static void* (*real_malloc)(size_t) = NULL;
  if (!real_malloc) {
    real_malloc = dlsym(RTLD_NEXT, "malloc");
  }

  void* ptr = real_malloc(size);
  fprintf(stderr, "malloc(%zu) = %p\n", size, ptr);
  return ptr;
}

void free(void* ptr) {
  static void (*real_free)(void*) = NULL;
  if (!real_free) {
    real_free = dlsym(RTLD_NEXT, "free");
  }

  fprintf(stderr, "free(%p)\n", ptr);
  real_free(ptr);
}
// LD_PRELOAD=./hook.so ls