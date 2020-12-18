#include "superblock.h"
#include "disk.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int init_sp_block() {
    spb.magic_num = MAGICNUM;
    spb.free_block_count = BLOCKNUM;
    spb.free_inode_count = INODENUM;
    spb.dir_inode_count = 0;
    for (int i = 0; i < BLOCKMAP; i++) {
        spb.block_map[i] = 0;
    }
    for (int i = 0; i < INODEMAP; i++) {
        spb.inode_map[i] = 0;
    }
}

int write_sp_block() {
    char buf[DEVICE_BLOCK_SIZE];
    init_buf(buf, DEVICE_BLOCK_SIZE);
    my_itoa(spb.magic_num, &buf[MAGICINDEX]);
    my_itoa(spb.free_block_count, &buf[BLOCKINDEX]);
    my_itoa(spb.free_inode_count, &buf[INODEINDEX]);
    my_itoa(spb.dir_inode_count, &buf[DIRINDEX]);
    for (int i = 0; i < BLOCKMAP; i++) {
        my_itoa(spb.block_map[i], &buf[BLOCKMAPINDEX+i]);
    }
    for (int i = 0; i < INODEMAP; i++) {
        my_itoa(spb.inode_map[i], &buf[INODEMAPINDEX+i]);
    }

    if (disk_write_block(0, buf) < 0) return 0;

    return 1;
}

int read_sp_block() {
    char buf[DEVICE_BLOCK_SIZE];
    if (disk_read_block(0, buf) < 0) {
        printf("Read from disk failed.\n");
        return 0;
    }
    spb.magic_num = my_atoi(&buf[MAGICINDEX], 6);
    spb.free_block_count = my_atoi(&buf[BLOCKINDEX], 4);
    spb.free_inode_count = my_atoi(&buf[INODEINDEX], 4);
    spb.dir_inode_count = my_atoi(&buf[DIRINDEX], 4);
    for (int i = 0; i < BLOCKMAP; i++) {
        spb.block_map[i] = my_atoi(&buf[BLOCKMAPINDEX+i], 1);
    }
    for (int i = 0; i < INODEMAP; i++) {
        spb.inode_map[i] = my_atoi(&buf[INODEMAPINDEX+i], 1);
    }
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

    for (int i = 0; i < BLOCKNUM; i++) {
        uint32_t block = spb.block_map[i];
        for (int j = 0; j < 32; j++) {
            if ((block >> j) & 1) continue;
            else {
                spb.free_block_count--;
                spb.block_map[i] &= 1 << j;
                write_sp_block(&spb);
                return i*INODENUM + j;
            }
        }
    }
    return -1;
}

int alloc_inode() {
    if (!spb.free_inode_count) return -1;

    for (int i = 0; i < INODENUM; i++) {
        uint32_t inode = spb.inode_map[i];
        for (int j = 0; j < 32; j++) {
            if ((inode >> j) & 1) continue;
            else {
                spb.free_inode_count--;
                spb.inode_map[i] &= 1 << j;
                write_sp_block(&spb);
                return i*INODENUM + j;
            }
        }
    }
    return -1;
}
