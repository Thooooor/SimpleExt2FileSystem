#ifndef FILE_H
#define FILE_H

#include "filesystem.h"

/**
 * @brief make file
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int make_file(char* path);

/**
 * @brief copy file
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int copy_file(char* argv1, char* argv2);

/**
 * @brief find a file
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int find_file(struct inode *dir, char* name, int* index);

/**
 * @brief initial a file
 * 
 * @return returns 1 on success, 0 otherwise. 
 */
int init_file(int* index);

#endif