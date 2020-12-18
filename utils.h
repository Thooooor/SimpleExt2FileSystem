#ifndef UTILS_H
#define UTILS_H

void my_itoa(int n, char* s);
int my_atoi(char* s, int length);
void init_buf(char* buf, int size);
void my_copy_string(char* a, char* b);
char* skip_space(char *s);
int get_path_and_name(char* argv, char (*path)[121]);
#endif