# 上课环境配置
```shell
sudo pacman -S nasm
```
# 可执行文件
- 一个操作系统中的对象
- 一个字节序列
```shell
xxd /bin/ls | vim -
```
x86 会的call指令的立即数会加到当前指令的尾部，请看下面的例子
```asm
Disassembly of section .text:

0000000000000000 <foo>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   b8 00 00 00 00          mov    $0x0,%eax
   9:   e8 00 00 00 00          call   e <foo+0xe> # 0xe 是下个指令的开头，即call 0 指令会跳到当前指令的结尾，这是因为x86指令可能有前缀，为了兼容。riscv会跳到指令的头
   e:   83 c0 01                add    $0x1,%eax
  11:   5d                      pop    %rbp
  12:   c3                      ret
```

# 动态链接和加载
- 阅读dlbox.c