#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <inttypes.h>

#define MAGICNUM 1234
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

/**
 * @brief initial super block
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_sp_block();

/**
 * @brief write super block into disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int write_sp_block();

/**
 * @brief read super block from disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int read_sp_block();

/**
 * @brief printsuper block information
 */
void print_sp_block();

/**
 * @brief alloc an empty block
 * 
 * @return returns index>=0 on success, -1 otherwise. 
 */
int alloc_block();

/**
 * @brief alloc an empty inode
 * 
 * @return returns index >=0 on success, -1 otherwise. 
 */
int alloc_inode();

#endif