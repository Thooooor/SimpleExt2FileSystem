#include "dir.h"
#include "disk.h"
#include "inode.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>


int make_dir(char* argv) {
    char name[NAMESIZE];
    init_buf(name, NAMESIZE);
    int num = get_path_and_name(argv, name);

    struct inode root;
    int root_index = 0;
    read_root_dir(&root);

    int index = 0;
    for (int i = 0; i < num-1; i++) {
        if (!find_dir(&root, cur_path[i], &index)) {
            init_dir(&index);
            insert_dir_item(&root, cur_path[i], Dir, root_index, index);
        }
        read_inode(&root, index);
        root_index = index;
    }

    if (!find_dir(&root, name, &index)) {
        init_dir(&index);
        insert_dir_item(&root, name, Dir, root_index, index);
    } else {
        printf("%s already existed.\n", name);
        return 0;
    }
    
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

int init_dir(int* index) {
    int inode_index = alloc_inode();
    *index = inode_index;

    if (inode_index < 0) {
        printf("alloc inode failed.\n");
        return 0;
    }

    struct inode* node = &inode[inode_index];
    if (!init_inode(node, 0, Dir, 1)) {
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
    node->size += ITEM_SIZE;

    struct dir_item items[ITEM_PER_BLOCK];
    for (int i = 0; i < ITEM_PER_BLOCK; i++) {
        if (!init_dir_item(&items[i], inode_index, 0, Dir, "")) {
            printf("initial dir item failed.\n");
            return 0;
        }
    }

    if (!write_dir_items(items, block_index)) return 0;
    if (!write_inode(node, inode_index)) return 0;
    if (!write_sp_block()) return 0;

    return 1;
}

int init_root_dir() {
    int index = 0;
    init_dir(&index);
    if (index != 0) {
        printf("initial root dir failed.\n");
        return 0;
    }
    return 1;
}

int read_root_dir(struct inode *root) {
    if (read_inode(root, 0)) return 1;
    return 0;
}

int write_dir_items(struct dir_item items[], int block_num) {
    char buf1[DEVICE_BLOCK_SIZE];
    char *item_point = (char *)items;

    for (int i = 0; i < DEVICE_BLOCK_SIZE; i++) buf1[i] = item_point[i];

    if (disk_write_block(block_num, buf1) < 0) return 0;
    return 1;
}

int insert_dir_item(struct inode* dir, char* name, int type, int inode_index, int index) {
    for (int i = 0; i < dir->link; i++) {
        struct dir_item items[ITEM_PER_BLOCK];
        read_dir_items(dir->block_point[i], items);
        for (int j = 0; j < ITEM_PER_BLOCK; j++) {
            if (!items[j].valid) {
                items[j].inode_id = index;
                items[j].type = type;
                items[j].valid = 1;
                strcpy(items[j].name, name);
                if (!write_dir_items(items, dir->block_point[i])) return 0;
                if (!write_inode(dir, inode_index)) return 0;
                return 1;
            }
        }
    }

    int new_block_index = alloc_block();
    dir->block_point[dir->link] = new_block_index;
    dir->link++;
    dir->size += ITEM_SIZE;

    struct dir_item items[ITEM_PER_BLOCK];
    for (int i = 0; i < ITEM_PER_BLOCK; i++) {
        if (!init_dir_item(&items[i], 0, 0, Dir, "")) {
            printf("initial dir item failed.\n");
            return 0;
        }
    }

    if (!write_dir_items(items, new_block_index)) return 0;
    if (!write_inode(dir, inode_index)) return 0;

    return 1;
}

int read_dir_items(int block_num, struct dir_item items[]) {
    char buf1[DEVICE_BLOCK_SIZE];

    if (disk_read_block(block_num, buf1) < 0) return 0;

    char *item_point = (char *)items;
    for (int i = 0; i < DEVICE_BLOCK_SIZE; i++) item_point[i] = buf1[i];
    return 1;
}

int find_dir(struct inode *dir, char* name, int* index) {
    for (int i = 0; i < dir->link; i++) {
        struct dir_item items[ITEM_PER_BLOCK];
        read_dir_items(dir->block_point[i], items);
        for (int j = 0; j < ITEM_PER_BLOCK; j++) {
            if (items[j].valid && !strcmp(name, items[j].name) && (items[j].type == Dir)) {
                *index = items[j].inode_id;
                return 1;
            }
        }
    }
    return 0;
}

int print_dir(struct inode *dir) {
    for (int i = 0; i < dir->link; i++) {
        struct dir_item items[ITEM_PER_BLOCK];
        read_dir_items(dir->block_point[i], items);
        for (int j = 0; j < ITEM_PER_BLOCK; j++) {
            if (items[j].valid) {
                print_dir_item(&items[j]);
            }
        }
    }
}

int print_dir_item(struct dir_item *item) {
    printf("name:%s\t", item->name);
    if (item->type == File) printf("file\t");
    else printf("dictionary\t");

    printf("\n");
}

int list_dir(char* argv) {
    char name[NAMESIZE];
    init_buf(name, NAMESIZE);
    int num = get_path_and_name(argv, name);

    struct inode root;
    int root_index = 0;
    read_root_dir(&root);

    for (int i = 0; i < num; i++) {
        int index = 0;
        if (!find_dir(&root, cur_path[i], &index)) {
            printf("Directionary dosen't exist.\n");
            return 0;
        }
        read_inode(&root, index);
        root_index = index;
    }
    print_dir(&root);
    
    return 1;
}