define hook-quit
  kill
end

set pagination off
target remote localhost:1234
file build/kernel-x86_64-qemu.elf
break on_interrupt
source visualize.py
continue