#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "inode.h"
#include "superblock.h"

#define INODE0 1

char current_path[256];


struct super_block spb;

struct inode inode[INODENUM];


struct dir_item
{
    unsigned int inode_id;
    unsigned int valid;
    unsigned int type;
    char name[121];
};

/**
 * @brief initial Ext2 file system
 * 
 * @return returns 0 on success, -1 otherwise. 
 * 
 * @note This function will initial Ext2 file system named "burger" as a vritual file system
 * If the file system is not found, it will try to create the file, and fill it with zeros of 4 MiB.
 * This function must be called before any calls to disk_read_block() and disk_write_block().
 * This function will fail if the disk is already opened.
 */
int init_system();

/**
 * @brief Open the Ext2 file system.
 * 
 * @return returns 0 on success, -1 otherwise. 
 * 
 * @note This function will open a file system named "burger" as a vritual file system
 * If the file is not found, it will try to create the file, and fill it with zeros of 4 MiB.
 * This function must be called before any calls to disk_read_block() and disk_write_block().
 * This function will fail if the disk is already opened.
 */
int open_system();

/**
 * @brief Close the Ext2 file system. 
 * 
 * @return returns 0 on success, -1 otherwise. 
 * 
 * @note This function will open a file named "disk" as a vritual disk
 * If the file is not found, it will try to create the file, and fill it with zeros of 4 MiB.
 * This function must be called before any calls to disk_read_block() and disk_write_block().
 * This function will fail if the disk is already opened.
 */
int close_system();

#endif