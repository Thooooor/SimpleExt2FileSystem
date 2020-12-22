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

/**
 * @brief initial an inode
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_inode(struct inode* node, int size, int type, int link);

/**
 * @brief write an inode into disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int write_inode(struct inode* node, int block);

/**
 * @brief read an inode from disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int read_inode(struct inode* node, int index);

/**
 * @brief print inode information
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int print_inode(struct inode *node);

#endif