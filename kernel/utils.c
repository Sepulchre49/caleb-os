void mem_copy(unsigned char *source, unsigned char *dest, int size) {
    const int MAX_COLS = 80;
    for (int i=0; i<2*MAX_COLS; i++)
        dest[i] = source[i];
}