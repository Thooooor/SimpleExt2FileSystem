#include "utils.h"
#include <stdio.h>
#include <ctype.h>

void my_itoa(int n, char* s) {
    char temp[10];
    int i, j, sign;
    i = 0;

    do {
        temp[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    j = 0;
    while (i) {
        s[j++] = temp[--i];
    }
    s[j] = '\0';

}

int my_atoi(char* s, int length) {
    int i, n;
    for(n=0, i=0; isdigit(s[i]) && i < length; i++) n = 10 * n + (s[i] - '0');
    
    return n;
}

void init_buf(char* buf, int size) {
    for (int i = 0; i < size; i++) {
        buf[i] = '0';
    }
}

void my_copy_string(char* a, char* b) {
    for (int i = 0; a[i] != '\0'; i++) {
        b[i] = a[i];
    }
}

char* skip_space(char* s) {
    while (isspace(*s)) s++;
    return s;
}

int get_path_and_name(char* input, char (*path)[121]) {
    int cnt = 0;
    if (input[0] == '.') input++;
    if (input[0] != '/') {
        for (int i = 0; input[0] != '/' && input[0] != '\0'; i++, input++) {
            path[cnt][i] = input[0];
        }
        cnt++;
    }
    
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '/') {
            i++;
            int j = 0;
            while (input[i+j] != '/' && input[i+j] != '\0') {
                path[cnt][j] = input[i+j];
                j++;
            }
            path[cnt][j] = '\0';
            cnt++;
            i += j - 1;
        }
    }
    return cnt;
}