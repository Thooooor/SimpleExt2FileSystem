#include "superblock.h"
#include "disk.h"
#include<stdlib.h>

int init_sp_block(sp_block *spb) {
    spb->magic_num = MAGICNUM;
    spb->free_block_count = BLOCKNUM;
    spb->free_inode_count = INODENUM;
    spb->dir_inode_count = 0;
    for (int i = 0; i < BLOCKNUM; i++) {
        spb->block_map[i] = 0;
    }
    for (int i = 0; i < INODENUM; i++) {
        spb->inode_map[i] = 0;
    }
}

int write_sp_block(sp_block *spb) {
    char buf[DEVICE_BLOCK_SIZE];
    // itoa(spb->magic_num, &buf[0]);
    // itoa(spb->free_block_count, &buf[1]);
    // itoa(spb->free_inode_count, &buf[2]);
    // itoa(spb->dir_inode_count, &buf[3]);
    for (int i = 0; i < BLOCKNUM; i++) {
        // itoa(spb->block_map[i], &buf[4+i]);
    }
    for (int i = 0; i < INODENUM; i++) {

    }

}

int read_sp_block(sp_block *spb) {

}