#include "superblock.h"
#include "disk.h"

int init_sp_block(sp_block *spb) {
    spb->magic_num = MAGICNUM;
    spb->free_block_count = BLOCKNUM;
    spb->free_inode_count = INODENUM;
    for (int i = 0; i < BLOCKNUM; i++) {
        spb->block_map[i] = 0;
    }
    for (int i = 0; i < INODENUM; i++) {
        spb->inode_map[i] = 0;
    }
}

int write_sp_block(sp_block *spb) {
    
}

int read_sp_block(sp_block *spb) {

}