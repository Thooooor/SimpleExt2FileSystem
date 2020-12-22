#include "disk.h"
#include "utils.h"
#include "superblock.h"
#include "inode.h"
#include <stdio.h>

int init_inode(struct inode* node, int size, int type, int link) {
    node->size = size;
    node->link = link;
    node->file_type = type;
    for (int i = 0; i < 6; i++) {
        node->block_point[i] = 0;
    }
    return 1;
}

int write_inode(struct inode* node, int index) {
    int block_num = INODE_START + index / INODE_PER_BLOCK;
    int inode_start = SINGLE_INODE * (index % INODE_PER_BLOCK);

    char buf[DEVICE_BLOCK_SIZE];
    if (disk_read_block(block_num, buf) < 0) return 0;

    char *node_p = (char *)node;
    for (int i = 0; i < SINGLE_INODE; i++) buf[inode_start + i] = node_p[i];

    if (disk_write_block(block_num, buf) < 0) return 0;

    return 1;
}

int read_inode(struct inode* node, int index) {
    int block_num = INODE_START + index / INODE_PER_BLOCK;
    int inode_start = SINGLE_INODE * (index % INODE_PER_BLOCK);

    char buf[DEVICE_BLOCK_SIZE];
    if (disk_read_block(block_num, buf)) return 0;

    char *node_p = (char *)node;
    for (int i = 0; i < SINGLE_INODE; i++) node_p[i] = buf[inode_start + i];

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

int print_inode(struct inode *node) {
    printf("size: %d\n", node->size);
    printf("filetype: ");
    if (node->file_type == File) printf("File\n");
    else printf("Dir\n");
    printf("link: %d\n", node->link);
    for (int i = 0; i < 6; i++) {
        printf("block[%d]: %d\n", i, node->block_point[i]);
    }
}