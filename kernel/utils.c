void mem_copy(unsigned char *source, unsigned char *dest, int size) {
    for (int i=source; i<dest; i++)
        dest[i] = source[i];
}