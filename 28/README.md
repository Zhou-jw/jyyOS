# 文件系统实现分析
## 文件的实现

文件 = “虚拟” 磁盘
API: read, write, ftruncate, ...
目录的实现

目录 = 文件/目录的集合
API: mkdir, rmdir, readdir, link, unlink, ...

我们没有 Random Access Memory

我们只有 block device
两个 API
bread(int bid, struct block *b);
bwrite(int bid, struct block *b);

实现：
read, write, ftruncate, ...
mkdir, rmdir, readdir, link, unlink, ...
如果用 block device 模拟 RAM，就会出现严重的读/写放大
我们需要更适合磁盘的数据结构

敌人：读/写放大

被迫读写连续的一块数据
朋友：局部性 + 缓存

适当地排布数据，使得临近的数据有 “一同访问” 的倾向
数据暂时停留在内存，延迟写回

# File Allocation Table (FAT) 文件系统
## 需求分析
- 目录中只有几个或十几个文件
- 文件以小文件为主

文件的实现方式
- struct block * 的链表
    - 任何高级的数据结构都显浪费

目录就是一个普通的文件 (虚拟磁盘；“目录文件”)
- 操作系统会对文件的内容作为目录的解读
    - 文件内容就是一个 struct dentry[];

## 用链表存储数据：两种数据
1. 在每个数据块后放置指针
优点：实现简单、无须单独开辟存储空间
缺点：数据的大小不是; 单纯的 lseek 需要读整块数据

2. 将指针集中存放在文件系统的某个区域
优点：局部性好；lseek 更快
缺点：集中存放的数据损坏将导致数据丢失

## 性能与可靠性
性能
- ＋ 小文件简直太合适了
- － 但大文件的随机访问就不行了
    - 4 GB 的文件跳到末尾 (4 KB cluster) 有 $2^{20}$ 次链表 next 操作
- 缓存能部分解决这个问题
- 在 FAT 时代，磁盘连续访问性能更佳
- 使用时间久的磁盘会产生碎片 (fragmentation)
- malloc 也会产生碎片，不过对性能影响不太大

可靠性
- 维护若干个 FAT 的副本防止元数据损坏 (额外的开销)
- 损坏的 cluster 在 FAT 中标记

# ext2/UNIX 文件系统
```shell
ls -i # print the index number of each file
```

