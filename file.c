#include "file.h"
#include "disk.h"
#include "utils.h"
#include "inode.h"
#include <stdio.h>

int make_file(char* argv) {
    char name[121];
    char path[121][121];
    int num = get_path_and_name(argv, path);
    for (int i = 0; path[num-1][i] != '\0'; i++) {
        name[i] = path[num-1][i];
    }
    num--;

    struct inode node;
    if (!init_inode(&node, 0, File, 1)) {
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
    node.size++;

    if (!write_inode(&node, inode_index+INODE0)) return 0;

    return 1;
}

int copy_file() {

}