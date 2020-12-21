#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <inttypes.h>

#define MAGICNUM 1234
#define MAGICINDEX 0
#define BLOCKINDEX 7
#define INODEINDEX 12
#define DIRINDEX 17
#define BLOCKMAPINDEX 22
#define INODEMAPINDEX 320
#define SUPERBLOCKSIZE 182
#define INODE_NUM 1024
#define BLOCK_NUM 2048
#define INODEMAP 32
#define BLOCKMAP 128

#define DISK_START 0
#define DISK_SIZE 2
#define INODE_START 2
#define INODE_SIZE 64
#define BLOCK_START 66
#define BLOCK_SIZE 4096

/**
 * 超级块
 **/
struct super_block
{
    int32_t magic_num;
    int32_t free_block_count;
    int32_t free_inode_count;
    int32_t dir_inode_count;
    uint32_t block_map[BLOCKMAP];
    uint32_t inode_map[INODEMAP];
};

struct super_block spb;

int init_sp_block();

int write_sp_block();

int read_sp_block();

void print_sp_block();

int alloc_block();

int alloc_inode();

#endif