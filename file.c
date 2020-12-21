#include "file.h"
#include "disk.h"
#include "utils.h"
#include "inode.h"
#include "dir.h"
#include <stdio.h>
#include <string.h>

int make_file(char* argv) {
    char name[NAMESIZE];
    init_buf(name, NAMESIZE);
    int num = get_path_and_name(argv, name);

    struct inode root;
    int root_index = 0;
    load_root_dir(&root);

    int index = 0;
    for (int i = 0; i < num-1; i++) {
        index = 0;
        if (!find_dir(&root, cur_path[i], &index)) {
            init_dir(&index);
            insert_dir_item(&root, cur_path[i], File, root_index, index);
        }
        read_inode(&root, index);
        root_index = index;
    }

    if (!find_file(&root, name, &index)) {
        init_file(&index);
        insert_dir_item(&root, name, File, root_index, index);
    } else {
        printf("%s already existed.\n", name);
        return 0;
    }

    return 1;
}

int copy_file(char* argv1, char* argv2) {
    char name[NAMESIZE];
    init_buf(name, NAMESIZE);
    int num = get_path_and_name(argv2, name);

    struct inode root;
    int root_index = 0;
    load_root_dir(&root);

    int index = 0;
    for (int i = 0; i < num-1; i++) {
        index = 0;
        if (!find_dir(&root, cur_path[i], &index)) {
            printf("source directionary dosen't exist.\n");
            return 0;
        }
        read_inode(&root, index);
        root_index = index;
    }

    if (!find_file(&root, name, &index)) {
        printf("source file dosen't exist.\n");
        return 0;
    }

    make_file(argv1);

    return 1;
}

int find_file(struct inode *dir, char* name, int* index) {
    for (int i = 0; i < dir->link; i++) {
        if (dir->block_point[i] < 0) continue;
        struct dir_item items[ITEM_PER_BLOCK];
        read_dir_item(dir->block_point[i], items);
        for (int j = 0; j < ITEM_PER_BLOCK; j++) {
            if (items[j].valid && !strcmp(name, items[j].name) && (items[j].type == File)) {
                *index = items[j].inode_id;
                return 1;
            }
        }
    }
    return 0;
}

int init_file(int* index) {
    int inode_index = alloc_inode();
    *index = inode_index;

    struct inode* node = &inode[inode_index];
    if (!init_inode(node, 0, File, 1)) {
        printf("initial inode failed.\n");
        return 0;
    }

    int block_index = alloc_block();
    if (block_index < 0) {
        printf("alloc block failed.\n");
        return 0;
    }
    node->block_point[0] = block_index;
    node->link = 1;

    if (!write_inode(node, inode_index)) return 0;
    if (!write_sp_block()) return 0;

    return 1;
}