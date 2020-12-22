# SimpleExt2FileSystem
HITsz OS操作系统实验5：实现简单的Ext2文件系统

run with:
```shell
gcc disk.c utils.c superblock.c inode.c dir.c file.c filesystem.c shell.c  -o main
./main
```

## 说明
完成如下功能：

1. 创建文件/文件夹（数据块可预分配）；
2. 读取文件夹内容；
3. 复制文件；
4. 关闭系统；
5. 系统关闭后，再次进入该系统还能还原出上次关闭时系统内的文件部署。

为实现的文件系统实现了简单的 shell 以及 shell 命令以展示实现的功能。实现了以下shell命令：
1. `ls` - 展示读取文件夹内容
2. `mkdir` - 创建文件夹
3. `touch` - 创建文件
4. `cp` - 复制文件
5. `shutdown` - 关闭系统
6. `help` - 指令帮助

## 模块
### 1. disk
封装与磁盘交互的底层函数

### 2. file system
相关功能：
1. 初始化文件系统 - `init_system`
2. 打开文件系统 - `open_system`
3. 关闭文件系统 - `close_system`
4. 封装指令，提供接口

### 3. super block
相关功能：
1. 初始化超级块 - `init_sp_block`
2. 将超级块写入disk - `write_sp_block`
3. 从disk中读出超级块 - `read_sp_block`
4. 打印超级块信息 - `print_sp_block`
5. 分配block - `alloc_block`
6. 分配inode - `alloc_inode`

### 4. inode
相关功能：
1. 初始化inode - `init_inode`
2. 将inode写入磁盘 - 'write_inode'
3. 读出inode - `read_inode`
4. 打印inode信息 - `print_inode`

### 5. file
相关功能:
1. 创建文件 - `make_file`
2. 复制文件 - `copy_file`
3. 查找文件 - `find_file`
4. 初始化文件 - `init_file`

### 6. dir
相关功能：
1. 创建文件夹 - `make_dir`
2. 查找文件夹
3. 初始化根目录
4. 加载根目录
5. 初始化文件夹
6. 初始化dir item
7. 将dir items写入disk
8. 读出 dir items
9. 打印文件信息
10. 打印文件夹信息
11. 列出指定路径文件夹下文件信息

### 7. shell
相关功能:
1. 主函数，运行shell - `main`
2. 将命令行输入根据空格进行划分 - `split`
3. 运行命令 - `run`
4. 支持指令：
```
ls
ls <dir path>
touch <file path>
cp <dst path> <src path>
mkdir <dir path>
help
shutdown
```

### 7. utils
封装工具函数