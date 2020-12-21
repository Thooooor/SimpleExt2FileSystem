#ifndef FILE_H
#define FILE_H

#include "filesystem.h"


int make_file(char* path);

int copy_file();

int find_file(struct inode *dir, char* name, int* index);

int init_file(int* index);

int insert_file(struct inode* dir, char* name, int inode_index, int index);

#endif