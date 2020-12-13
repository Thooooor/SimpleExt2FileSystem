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
    
    for(n=0; isdigit(s[i]) && i < length; i++) n = 10 * n + (s[i] - '0');
    
    return n;
}