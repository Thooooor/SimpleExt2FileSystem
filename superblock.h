#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#define MAGICNUM 1234
#define MAGICINDEX 0
#define BLOCKINDEX 7
#define INODEINDEX 12
#define DIRINDEX 17
#define BLOCKMAPINDEX 22
#define INODEMAPINDEX 150
#define SUPERBLOCKSIZE 182
#define INODENUM 32
#define BLOCKNUM 128

/**
 * 超级块
 **/
struct super_block
{
    int magic_num;
    int free_block_count;
    int free_inode_count;
    int dir_inode_count;
    unsigned int block_map[BLOCKNUM];
    unsigned int inode_map[INODENUM];
};

int init_sp_block(struct super_block *spb);

int write_sp_block(struct super_block *spb);

int read_sp_block(struct super_block *spb);

void print_sp_block(struct super_block *spb);

int alloc_block(int n);
#endif