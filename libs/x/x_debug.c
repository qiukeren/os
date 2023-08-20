#include "x_debug.h"

void x_debug_print_file_content(char* filename) {
    int c;
    FILE* file;
    file = fopen(filename, "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            putchar(c);
        }
        fclose(file);
    }
    putchar('\n');
}

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void dump_hex(const uint8_t* buf, uint32_t size, uint32_t number) {
    int i, j;

    for (i = 0; i < size; i += number) {
        printf("%08X: ", i);

        for (j = 0; j < number; j++) {
            if (j % 8 == 0) {
                printf(" ");
            }
            if (i + j < size)
                printf("%02X ", buf[i + j]);
            else
                printf("   ");
        }
        printf(" ");

        for (j = 0; j < number; j++) {
            if (i + j < size) {
                printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        printf("\n");
    }
}
