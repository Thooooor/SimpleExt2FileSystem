#ifndef DIR_H
#define DIR_H

#include "filesystem.h"
#include <inttypes.h>

#define ITEM_SIZE 128
#define ITEM_PER_BLOCK 4
#define NAMESIZE 121

struct dir_item
{
    uint32_t inode_id;
    uint16_t valid;
    uint8_t type;
    char name[NAMESIZE];
};

/**
 * @brief make a dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int make_dir(char* path);

/**
 * @brief initial a dir item
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_dir_item(struct dir_item* item, int inode_id, int valid, int type, char* name);

/**
 * @brief initial a dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_dir(int* index);

/**
 * @brief initial root dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_root_dir();

/**
 * @brief read root dir from disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int read_root_dir(struct inode *root);

/**
 * @brief write dir items imto disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int write_dir_items(struct dir_item* item, int block_num);

/**
 * @brief insert an dir item into a dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int insert_dir_item(struct inode* dir, char* name, int type, int inode_index, int index);

/**
 * @brief find a dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int find_dir(struct inode *dir, char* name, int* index);

/**
 * @brief read dir items from disk
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int read_dir_items(int block_num, struct dir_item items[]);

/**
 * @brief print a dir item information
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int print_dir_item(struct dir_item *item);

/**
 * @brief print a dir information
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int print_dir(struct inode *dir);

/**
 * @brief list dir items in a dir
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int list_dir(char* argv);

#endif