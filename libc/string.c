#include "string.h"

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char c, char s[]) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

bool compare(char x[], char y[]) {
    int lenX = strlen(x);
    int lenY = strlen(y);
    if (lenX != lenY) return false;

    for (int i=0; i<lenX; i++) {
        if (x[i] != y[i]) return false;
    }
    return true;
}

void substring(char src[], char dest[], int start, int end) {
    if (strlen(src) < (start-end)) return;
    for (int i=start; i<end; i++) {
        dest[i-start] = src[i];
    }
    dest[end+1] = '\0';
}