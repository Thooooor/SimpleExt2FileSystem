#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H
#include "filesystem.h"

#define MAGICINDEX 0
#define BLOCKINDEX 4
#define INODEINDEX 8
#define DIRINDEX 12
#define BLOCKMAPINDEX 16
#define INODEMAPINDEX 144
#define SUPERBLOCKSIZE 176

int init_sp_block(sp_block *spb);

int write_sp_block(sp_block *spb);

int read_sp_block(sp_block *spb);

void print_sp_block(sp_block *spb);
#endif