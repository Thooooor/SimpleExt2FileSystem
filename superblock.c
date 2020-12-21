#include "superblock.h"
#include "disk.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int init_sp_block() {
    spb.magic_num = MAGICNUM;
    spb.free_block_count = BLOCK_NUM;
    spb.free_inode_count = INODE_NUM;
    spb.dir_inode_count = 0;
    for (int i = 0; i < BLOCKMAP; i++) {
        spb.block_map[i] = 0;
    }
    for (int i = 0; i < INODEMAP; i++) {
        spb.inode_map[i] = 0;
    }
}

int write_sp_block() {
    char buf[DEVICE_BLOCK_SIZE*2];
    char *spb_point = (char *)&spb;
    for (int i = 0; i < sizeof(spb); i++) buf[i] = spb_point[i];

    if (disk_write_block(0, buf) < 0) return 0;
    if (disk_write_block(1, &buf[DEVICE_BLOCK_SIZE]) < 0) return 0;
    return 1;
}

int read_sp_block() {
    char buf[DEVICE_BLOCK_SIZE*2];
    if (disk_read_block(0, buf) < 0) {
        printf("Read from disk failed.\n");
        return 0;
    }
    if (disk_read_block(1, &buf[DEVICE_BLOCK_SIZE]) < 0) {
        printf("Read from disk failed.\n");
        return 0;
    }

    char *p = (char *)&spb;
    for (int i = 0; i < sizeof(spb); i++) p[i] = buf[i]; 
    
    return 1;
}

void print_sp_block() {
    printf("magic number: %d\n", spb.magic_num);
    printf("free block count: %d\n", spb.free_block_count);
    printf("free inode count: %d\n", spb.free_inode_count);
    printf("dir inode count: %d\n", spb.dir_inode_count);
}

int alloc_block() {
    if (!spb.free_block_count) return -1;

    for (int i = 0; i < BLOCKMAP; i++) {
        uint32_t block = spb.block_map[i];
        for (int j = 0; j < 32; j++) {
            if ((block >> j) & 1) continue;
            else {
                spb.free_block_count--;
                spb.block_map[i] |= 1 << j;
                // write_sp_block();
                return i*32 + j;
            }
        }
    }
    return -1;
}

int alloc_inode() {
    if (!spb.free_inode_count) return -1;

    for (int i = 0; i < INODEMAP; i++) {
        uint32_t inode = spb.inode_map[i];
        for (int j = 0; j < 32; j++) {
            printf("i:%d j:%d\n", i, j);
            if ((inode >> j) & 1) continue;
            else {
                spb.free_inode_count--;
                printf("before:%d ", spb.inode_map[i]);
                spb.inode_map[i] |= 1 << j;
                printf("after:%d\n", spb.inode_map[i]);
                // write_sp_block();
                return i*32 + j;
            }
        }
    }
    return -1;
}
