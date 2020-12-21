#ifndef DIR_H
#define DIR_H

#include "filesystem.h"
#include <inttypes.h>

#define ITEM_SIZE 128
#define ITEM_PER_BLOCK 8
#define NAMESIZE 121

struct dir_item
{
    uint32_t inode_id;
    uint16_t valid;
    uint8_t type;
    char name[NAMESIZE];
};


int make_dir(char* path);

int init_dir_item(struct dir_item* item, int inode_id, int valid, int type, char* name);

int init_root_dir();

int write_dir_item(struct dir_item* item, int block_num);

int find_dir(char* argv[], int argc);

int read_dir_item(int block_num, struct dir_item items[]);

#endif