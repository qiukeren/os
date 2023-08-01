#include "x_paths.h"

void x_touch(const char* filename) {
    FILE *fd = fopen(filename, "a+");

    if (fd == NULL) {
        perror("Unable to touch file");
        return;
    }

    fclose(fd);
}

void x_mkdir(char* path, mode_t mode) {
    char opath[128];
    char* p;
    size_t len;

    strncpy(opath, path, sizeof(opath));
    opath[sizeof(opath) - 1] = '\0';
    len = strlen(opath);
    if (len == 0)
        return;
    else if (opath[len - 1] == '/')
        opath[len - 1] = '\0';
    for (p = opath; *p; p++)
        if (*p == '/') {
            *p = '\0';
            if (access(opath, F_OK))
                mkdir(opath, mode);
            *p = '/';
        }
    if (access(opath, F_OK)) /* if path is not terminated with / */
        mkdir(opath, mode);
}