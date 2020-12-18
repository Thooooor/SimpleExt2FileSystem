#include "dir.h"
#include "disk.h"
#include "inode.h"
#include "utils.h"


int make_dir(char* path, char* name, int inode, int type) {
    struct inode node;
    if (!init_inode(&node, 0, Dir, 1)) return 0;


}

int init_dir_item(struct dir_item* item, int inode_id, int valid, int type, char* name) {
    item->inode_id = inode_id;
    item->valid = valid;
    item->type = type;
    my_copy_string(name, item->name);
    return 1;
}

int init_root_dir() {
    struct inode root_node;
    init_inode(&root_node, 0, Dir, 1);
    int inode_index = alloc_inode();
    if (inode_index < 0) {
        printf("No enough inode.\n");
        return 0;
    }
    struct dir_item root_dir;
    init_dir_item(&root_dir, inode_index, 1, Dir, "root");
    return 1;
}
