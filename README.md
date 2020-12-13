run with
```shell
gcc shell.c filesystem.c superblock.c disk.c -o main
./main
```

## 模块
### 1. disk
封装与磁盘交互的底层函数

### 2. file system
相关功能：
1. 初始化文件系统`init_system`
2. 打开文件系统`ope_system`
3. 关闭文件系统`close_system`

### 3. super block
相关功能：
1. 初始化超级块`init_sp_block`
2. 将超级块写入disk`write_sp_block`
3. 从disk中读出超级块`read_sp_block`
4. 打印超级块信息`print_sp_block`

### 4. file
相关功能:
1. 创建文件`make_file`
2. 复制文件`copy_file`
### 5. folder
相关功能；
1. 创建文件夹`make_dir`

### 6. shell
相关功能:
1. 主函数，运行shell `main`
2. 将命令行输入根据空格进行划分 `split`
3. 运行命令 `run`
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