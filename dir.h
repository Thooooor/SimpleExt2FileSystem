#ifndef DIR_H
#define DIR_H

#include "filesystem.h"
#include <inttypes.h>

struct dir_item
{
    uint32_t inode_id;
    uint16_t valid;
    uint8_t type;
    char name[121];
};

int make_dir();

int init_dir_item(struct dir_item* item, int inode_id, int valid, int type, char* name);

int init_root_dir();

#endif