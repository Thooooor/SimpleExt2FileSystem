#include "filesystem.h"
#include "disk.h"
#include "superblock.h"
#include "inode.h"
#include "dir.h" 
#include <stdio.h>


int init_system() {
    init_sp_block(&spb);
    print_sp_block(&spb);
    if (!write_sp_block(&spb)) {
        printf("Initial super bolck failed.\n");
        return -1;
    }
    for (int i = 0; i < INODENUM; i++) {
        if (!init_inode(&inode[i], 0, File, 0)) {
            printf("Initial Inode failed.\n");
            return -1;
        }
        if (!write_inode(&inode[i], INODE0+i)) {
            printf("Write Inode failed.\n");
            return -1;
        }
    }
    if (!init_root_dir()) {
        printf("Initial root failde.\n");
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
        for (int i = 0; i < INODENUM; i++) {
            if (!read_inode(&inode[i], INODE0+i)) {
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
    printf("Save super bolck Suceeded.\n");

    if (close_disk() < 0) {
        printf("Close disk failed.\n");
        return -1;
    }
    return 1;
}