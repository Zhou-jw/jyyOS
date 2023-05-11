int bar();

int foo() {
    return bar() + 1;
}
// gcc -c a.c && objdump -d a.o