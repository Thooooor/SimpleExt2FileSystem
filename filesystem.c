#include "filesystem.h"
#include "disk.h"
#include "superblock.h"
#include <stdio.h>

sp_block *spb;

int init_system() {
    init_sp_block(spb);
    
    if (!write_sp_block(spb)) {
        printf("Initial super bolck failed.\n");
        return -1;
    }
    printf("Initial super bolck succeded.Enjoy your Burger.\n");
    return 1;
}

int open_system() {
    if (open_disk()<0) {
        printf("Open disk error.\n");
        return -1;
    }
    if (read_sp_block(spb) && spb->magic_num == MAGICNUM) {
        printf("Enjoy your Burger.\n");
    } else {
        printf("File System Unkonwn or didn't exist. Format disk and build a burger file system?(y/n)\n");
        char option;
        scanf("%c", &option);
        if (option == 'y') {
            init_system();
            return 1;
        } else {
            return -1;
        }
    }
}

int close_system() {
    if (!write_sp_block(spb)) {
        printf("Save super bolck failed.\n");
        return -1;
    }

    if (close_disk() < 0) {
        printf("Close disk failed.\n");
    }

    printf("Hoped you enjoyed your burger. See you.\n");
    return 1;
    
}