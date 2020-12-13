#include "filesystem.h"
#include "disk.h"
#include "superblock.h"
#include <stdio.h>


int init_system() {
    init_sp_block(&spb);
    print_sp_block(&spb);
    if (!write_sp_block(&spb)) {
        printf("Initial super bolck failed.\n");
        return -1;
    }
    printf("Initial super bolck succeded. Enjoy your Burger.\n");
    return 1;
}

int open_system() {
    if (open_disk()<0) {
        printf("Open disk error.\n");
        return -1;
    }
    if (read_sp_block(&spb) && spb.magic_num == MAGICNUM) {
        printf("Find existed Ext2. Enjoy your Burger.\n");
        return -1;
    } else {
        printf("File System Unkonwn or didn't exist. Format disk and build a burger file system.\n");
        init_system();
        return 1;
    }
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