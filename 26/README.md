# 输入输出设备
## I/O 设备
- 等效为几个寄存器+数据+指令(reg, data, command)
- 约定好几组线
- 通过握手信号从线上读出/写入数据
- 每一组线都有自己的地址

## 越来越多的 I/O 设备
总线：一个特殊的 I/O设备
- 把受到的地址和数据转发到相应设备上
- 这样 CPU 只要连接一个总线就行
- lspci -tv 和lsusb -tv查看总线上的设备

## Diret Memory Access(DMA)
- 一个专门执行"Memcpy"程序的CPU
- mem -> mem
- device -> mem
- men -> device
- sudo cat /proc/iomem

# GPU 和 加速器
