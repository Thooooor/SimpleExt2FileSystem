#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"
#include "filesystem.h"
#include "dir.h"

int main() {
    printf("Welcome to FileSystem shell.\n");
    if (!open_system()) {
        printf("Failed to open FileSystem.\n");
        shutdown();
    } 

    while(1) {
        printf(">_> ");
        fgets(buf, SHELLBUFF, stdin);
        split();
        run();
    }
}

void split() {
    char* cmd = buf;
    cmd = skip_space(cmd);
    char* space = strchr(cmd, ' ');
    int i = 0;
    while (space != NULL) {
        space[0] = '\0';
        argv[i] = cmd;
        i++;
        cmd = skip_space(space + 1);
        space = strchr(cmd, ' ');
    }

    if (cmd[0] != '\0') {
        argv[i] = cmd;
        space = strchr(cmd, '\n');
        space[0] = '\0';
        i++;
    }
    argv[i] = NULL;
    argc = i;
}

void run() {
    char* command = argv[0];
    if (!strcmp(command, "ls")) {
        printf("command: ls ");
        if (argc > 2) {
            printf("\nToo many arguments for 'ls'\n");
        } else if (argc == 2) {
            printf("%s\n", argv[1]);
        } else {
            printf("\n");
        }
    } else if (!strcmp(command, "mkdir")) {
        printf("command: mkdir ");
        if (argc > 2) {
            printf("\ntoo mant arguments for 'mkdir'\n");
        } else if (argc == 2) {
            printf("%s\n", argv[1]);
            if (!make_dir("", argv[1])) {
                printf("make dir failed.\n");
            } else {
                printf("make dir %s succeeded.\n", argv[1]);
            }
        } else {
            printf("\ntoo few arguments for 'mkdir'\n");
        }
    } else if (!strcmp(command, "touch")) {
        printf("command: touch");
    } else if (!strcmp(command, "cp")) {
        printf("command: cp");
    } else if (!strcmp(command, "shutdown")) {
        shutdown();
    } else if (!strcmp(command, "help")) {
        help();
    } else {
        printf("'%s': command not found.\nSee \'help\'\n", command);
    }
}

void help() {
    printf("command:\n");
    printf("ls <dir path>\n");
    printf("touch <file path>\n");
    printf("cp <dst path> <src path>\n");
    printf("mkdir <dir path>\n");
    printf("shutdown\n");
    printf("help\n");
}

char* skip_space(char* s) {
    while (isspace(*s)) s++;
    return s;
}

void shutdown() {
    if (close_system()) printf("Thanks for using ^_^\n");
    exit(0);
}