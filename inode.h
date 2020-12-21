#ifndef INODE_H
#define INODE_H

#include <inttypes.h>

#define File 1
#define Dir 2
#define BLOCKSIZE 6
#define SINGLE_INODE 32
#define INODE_PER_BLOCK 16

struct inode
{
    uint32_t size;
    uint16_t file_type;
    uint16_t link;
    uint32_t block_point[6];
};

// 1: succeeded 0:failed
int init_inode(struct inode* node, int size, int type, int link);

int copy_inode(struct inode* a, struct inode* b);

int write_inode(struct inode* node, int block);

int read_inode(struct inode* node, int index);

int check_inode();

int print_inode(struct inode *node);

#endif