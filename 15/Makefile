NAME := kernel
SRCS := thread-os.c
export AM_HOME = /home/zjw/os-workbench/abstract-machine
export ARCH := x86_64-qemu
include $(AM_HOME)/Makefile

debug:
	qemu-system-x86_64 -s -S build/kernel-x86_64-qemu &
	gdb -x init.gdb

clean:
	rm -rf build/