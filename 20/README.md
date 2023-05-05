# musl libc
download musl
为了能够gdb musl，编译musl需要添加 -g
```shell
./configure CFLAGS='-g'
make 
make install
```
musl-gcc is a script and located in '/usr/local/musl/bin/musl-gcc'
```shell
vim /usr/local/musl/bin/musl-gcc
```
添加到/usr/bin
```shell
sudo ln -s /usr/local/musl/bin/musl-gcc /usr/bin/musl-gcc
```

# 动态内存管理
小对象分配比较频繁，可以用一个列表，
大对象上锁
