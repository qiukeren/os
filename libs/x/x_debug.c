#include <stdio.h>

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
