// By GPT-4; slightly modified

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>

#define PAGE_SHIFT 12
#define PAGEMAP_LENGTH 8

void *get_physical_address(void *va) {
    int pagemap_fd;
    uint64_t value;
    uint64_t file_offset = ((uint64_t)va / (1ULL << PAGE_SHIFT)) * PAGEMAP_LENGTH;
    char pagemap_file[64];

    sprintf(pagemap_file, "/proc/%d/pagemap", getpid());
    pagemap_fd = open(pagemap_file, O_RDONLY);
    if (pagemap_fd < 0) {
        perror("Error opening pagemap file");
        return NULL;
    }

    if (pread(pagemap_fd, &value, PAGEMAP_LENGTH, file_offset) != PAGEMAP_LENGTH) {
        perror("Error reading pagemap");
        close(pagemap_fd);
        return NULL;
    }

    close(pagemap_fd);

    if (value & (1ULL << 63)) {
        return (void*)(((value & ((1ULL << 55) - 1)) << PAGE_SHIFT)
          + ((uint64_t)va & ((1ULL << PAGE_SHIFT) - 1)));
    } else {
        return NULL;
    }
}

int main() {
    void *handle;
    void (*printf_ptr)(const char *, ...);

    // Load the libc library
    handle = dlopen("libc.so.6", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Get the address of printf
    printf_ptr = dlsym(handle, "printf");
    if (!printf_ptr) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Close the library handle
    dlclose(handle);

    char *ptr = malloc(1);

    printf("ptr: %p -> %p\n", ptr, get_physical_address(ptr));
    printf("main: %p -> %p\n", main, get_physical_address(main));
    printf("printf: %p -> %p\n", printf_ptr, get_physical_address(printf_ptr));

    free(ptr);

    while (1) {
      sleep(1);
    }

    return 0;
}