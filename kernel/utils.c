#include "utils.h"

void mem_copy(u8int *source, u8int *dest, s32int size) {
    const int MAX_COLS = 80;
    for (int i=0; i<2*MAX_COLS; i++)
        dest[i] = source[i];
}

void mem_set(u8int *dest, u8int ch, u32int count) {
    for (int i=0; i<count; i++) {
        dest[i] = ch;
    }
}

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