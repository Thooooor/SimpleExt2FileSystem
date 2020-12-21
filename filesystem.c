#include "filesystem.h"
#include "disk.h"
#include "superblock.h"
#include "inode.h"
#include "dir.h" 
#include "file.h"
#include <stdio.h>


int init_system() {
    init_sp_block(&spb);
    print_sp_block(&spb);
    if (!write_sp_block(&spb)) {
        printf("Initial super bolck failed.\n");
        return -1;
    }
    for (int i = 0; i < INODE_NUM; i++) {
        if (!init_inode(&inode[i], 0, File, 0)) {
            printf("Initial Inode failed.\n");
            return -1;
        }
        if (!write_inode(&inode[i], i)) {
            printf("Write Inode failed.\n");
            return -1;
        }
    }
    if (!init_root_dir()) {
        printf("Initial root failed.\n");
        return 0;
    }
    printf("Initial super bolck succeded. Enjoy your time.\n");
    return 1;
}

int open_system() {
    if (open_disk()<0) {
        printf("Open disk error.\n");
        return 0;
    }
    if (read_sp_block(&spb) && spb.magic_num == MAGICNUM) {
        print_sp_block(&spb);
        for (int i = 0; i < INODE_NUM; i++) {
            if (!read_inode(&inode[i], i)) {
                printf("Load Inode failed.\n");
                return -1;
            }
        }
        printf("Find existed Ext2. Enjoy your time.\n");

    } else {
        printf("File System Unkonwn or didn't exist. Format disk and build a new file system.\n");
        init_system();
    }
    return 1;
}

int close_system() {
    if (!write_sp_block(&spb)) {
        printf("Save super bolck failed.\n");
        return -1;
    }
    printf("Save super bolck Succeeded.\n");

    if (close_disk() < 0) {
        printf("Close disk failed.\n");
        return -1;
    }
    printf("Close Disk.\n");
    return 1;
}

void mkdir(char* argv[], int argc) {
    if (argc > 2) {
        printf("\ntoo mant arguments for 'mkdir'\n");
    } else if (argc == 2) {
        if (!make_dir(argv[1])) {
            printf("make dir failed.\n");
        } else {
            printf("make dir %s succeeded.\n", argv[1]);
        }
    } else {
        printf("\ntoo few arguments for 'mkdir'\n");
    }
}

void touch(char* argv[], int argc) {
    printf("command: touch ");
    if (argc > 2) printf("\ntoo many arguments for 'touch'\n");
    else if (argc == 2) {
        printf("%s\n", argv[1]);
        if (make_file(argv[1])) {
            printf("touch %s succeeded.\n", argv[1]);
        } else {
            printf("touch %s failed\n", argv[1]);
        }
    } else {
        printf("\ntoo few arguments for 'touch'\n");
    }
}

void ls(char* argv[], int argc) {
    printf("command: ls\n");
    if (argc > 2) {
        printf("\nToo many arguments for 'ls'\n");
    } else if (argc == 2) {
        printf("%s\n", argv[1]);
    } else {
        struct inode root;
        load_root_dir(&root);
        print_inode(&root);
        print_dir(&root);
    }
}

void cp(char* argv[], int argc) {

}