#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"


int main() {

    printf("Welcome to FileSystem shell.\n");
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
        printf("command: mkdir");
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
}

char* skip_space(char* s) {
    while (isspace(*s)) s++;
    return s;
}

void shutdown() {
    printf("Thanks for using ^_^.\n");
    exit(0);
}