#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "inode.h"
#include "superblock.h"

struct inode inode[INODE_NUM];


/**
 * @brief initial Ext2 file system
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_system();

/**
 * @brief Open the Ext2 file system.
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int open_system();

/**
 * @brief Close the Ext2 file system. 
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int close_system();

/**
 * @brief make dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
void mkdir(char* argv[], int argc);

/**
 * @brief make file
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
void touch(char* argv[], int argc);

/**
 * @brief list dst dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
void ls(char* argv[], int argc);

/**
 * @brief copy file from dst to src
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
void cp(char* argv[], int argc);

#endif