#include "dir.h"
#include "disk.h"
#include "inode.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>


int make_dir(char* argv) {
    char name[NAMESIZE];
    printf("get %s\n", argv);
    char path[NAMESIZE][NAMESIZE];
    int num = get_path_and_name(argv, path, name);

    struct inode node;
    if (!init_inode(&node, 0, Dir, 1)) {
        printf("initial inode failed.\n");
        return 0;
    }

    int inode_index = alloc_inode();
    if (inode_index < 0) {
        printf("alloc inode failed.\n");
        return 0;
    }
    
    int block_index = alloc_block();
    if (block_index < 0) {
        printf("alloc block failed.\n");
        return 0;
    }

    node.block_point[0] = block_index;
    printf("block: %d\n", block_index);
    node.size += ITEM_SIZE;

    struct dir_item item;
    if (!init_dir_item(&item, inode_index, 1, Dir, name)) {
        printf("initial dir item failed.\n");
        return 0;
    }

    if (!write_dir_item(&item, block_index)) return 0;
    
    if (!write_inode(&node, inode_index)) return 0;
    
    return 1;
}

int init_dir_item(struct dir_item* item, int inode_id, int valid, int type, char* name) {
    item->inode_id = inode_id;
    item->valid = valid;
    item->type = type;
    for (int i = 0; i < NAMESIZE; i++) item->name[i] = '\0';
    my_copy_string(name, item->name);
    return 1;
}

int init_root_dir() {
    if (!make_dir(".")) return 0;
    return 1;
}

int write_dir_item(struct dir_item items[], int block_num) {
    char buf1[DEVICE_BLOCK_SIZE];
    char buf2[DEVICE_BLOCK_SIZE];
    char *item_point = (char *)items;
    for (int i = 0; i < DEVICE_BLOCK_SIZE; i++) {
        buf1[i] = item_point[i];
        buf2[i] = item_point[DEVICE_BLOCK_SIZE + i];
    }

    if (disk_write_block(block_num, buf1) < 0) return 0;
    if (disk_write_block(block_num + 1, buf2) < 0) return 0; 

    return 1;
}

int read_dir_item(int block_num, struct dir_item items[]) {
    char buf1[DEVICE_BLOCK_SIZE];
    char buf2[DEVICE_BLOCK_SIZE];
    if (disk_read_block(block_num, buf1) < 0) return 0;
    if (disk_read_block(block_num+1, buf2) < 0) return 0;

    char *item_point = (char *)items;
    for (int i = 0; i < DEVICE_BLOCK_SIZE; i++) {
        item_point[i] = buf1[i];
        item_point[DEVICE_BLOCK_SIZE + i] = buf2[i];
    }

    return 1;
}

int find_dir(char* argv[], int argc) {
    struct inode node;
    printf("begin find.\n");
    for (int i = 0; i < INODE_NUM; i++) {
        if (!read_inode(&node, i)) return -1;
        if (node.file_type != Dir) continue;

        for (int j = 0; j < 6; j++) {
            if (node.block_point[j] < 0) continue;

            struct dir_item items[ITEM_PER_BLOCK];
            if (!read_dir_item(node.block_point[j], items)) return -1;

            for (int k = 0; k < ITEM_PER_BLOCK; k++) {
                if (!items[k].valid) continue;
                printf("name: %s.\n", items[k].name);
                if (!strcmp(argv[argc-1], items[k].name)) {
                    return items[k].inode_id;
                }
            }
        }
    }
    return -1;
}
