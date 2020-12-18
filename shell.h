#ifndef SHELL_H
#define SHELL_H

#define SHELLBUFF 128

char* argv[SHELLBUFF];
int argc = 0;
char buf[SHELLBUFF];
void split();
void run();
void help();
void shutdown();
#endif