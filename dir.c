#include "dir.h"
#include "disk.h"
#include "inode.h"
#include "utils.h"


int make_dir(char* path, char* name) {
    struct inode node;
    if (!init_inode(&node, 0, Dir, 1)) return 0;

    int inode_index = alloc_inode();
    if (inode_index < 0) return 0;

    int block_index = alloc_block();
    if (block_index < 0) return 0;
    node.block_point[0] = block_index;
    node.size++;

    struct dir_item item;
    if (!init_dir_item(&item, inode_index, 1, Dir, name)) return 0;

    if (!write_dir_item(&item, block_index)) return 0;
    if (!write_inode(&node, inode_index+INODE0)) return 0;

    return 1;
}

int init_dir_item(struct dir_item* item, int inode_id, int valid, int type, char* name) {
    item->inode_id = inode_id;
    item->valid = valid;
    item->type = type;
    my_copy_string(name, item->name);
    return 1;
}

int init_root_dir() {
    if (!make_dir("", "root")) return 0;
    return 1;
}

int write_dir_item(struct dir_item* item, int block_num) {
    char buf[DEVICE_BLOCK_SIZE];
    my_itoa(item->inode_id, &buf[0]);
    my_itoa(item->valid, &buf[5]);
    my_itoa(item->type, &buf[7]);
    for (int i = 0; i < 121; i++) {
        buf[8+i] = item->name[i];
    }
    if (disk_write_block(block_num, buf) < 0) return 0;
    return 1;
}
