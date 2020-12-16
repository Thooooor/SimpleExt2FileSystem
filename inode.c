#include "disk.h"
#include "utils.h"
#include "superblock.h"
#include "inode.h"
#include <stdio.h>

int init_inode(struct inode* node, int size, int type, int link) {
    // if (!check_inode()) return 0;
    // if (!alloc_block(BLOCKSIZE)) return 0;
    node->size = 0;
    node->link = 1;
    node->file_type = type;
    return 1;
}

int copy_inode(struct inode* a, struct inode* b) {
    if (!check_inode()) return 0;
    if (!alloc_block(BLOCKSIZE)) return 0;
    b->size = a->size;
    b->link = b->link;
    b->file_type = a->file_type;
    return 1;
}

int write_inode(struct inode* node, int block_num) {
    char buf[DEVICE_BLOCK_SIZE];
    my_itoa(node->size, &buf[0]);
    my_itoa(node->file_type, &buf[1]);
    my_itoa(node->link, &buf[2]);
    for (int i = 0; i < BLOCKSIZE; i++) {
        my_itoa(node->block_point[i], &buf[3+i]);
    }
    if (disk_write_block(block_num, buf) < 0) return 0;
    return 1;
}

int read_inode(struct inode* node, int block_num) {
    char buf[DEVICE_BLOCK_SIZE];
    if (disk_read_block(block_num, buf)) return 0;
    node->size = my_atoi(&buf[0], 1);
    node->file_type = my_atoi(&buf[1], 1);
    node->link = my_atoi(&buf[2], 1);

    for (int i = 0; i < BLOCKSIZE; i++) {
        node->block_point[i] = my_atoi(&buf[3+i], 1);
    }
    return 1;
}

int check_inode() {
    struct super_block sp;
    if (!read_sp_block(&sp)) return 0;
    printf("Inode read:\n");
    print_sp_block(&sp);
    if (!sp.free_inode_count) {
        printf("No enough memory for inode.\n");
        return 0;
    }

    return 1;
}
