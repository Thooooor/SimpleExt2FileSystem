#ifndef INODE_H
#define INODE_H
#include "filesystem.h"

#define FILE 1
#define DIR 2
#define BLOCKSIZE 6
#define NODESIZE 12

// 1: succeeded 0:failed
int init_inode(struct inode* node, int size, int type, int link);

int copy_inode(struct inode* a, struct inode* b);

int write_inode(struct inode* node, int block);

int read_inode(struct inode* node, int index);

int check_inode();

int alloc_block(int n);

#endif