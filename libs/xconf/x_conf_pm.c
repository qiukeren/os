#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include "x_conf_paths.h"
#include "x_conf_pm.h"

int _filter(const struct dirent* name) {
    return 1;
}

void x_pm_load_packages() {
    struct dirent** namelist;
    int n;

    n = scandir(X_PM_PACKAGELIST_DIR, &namelist, _filter, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    while (n--) {
        printf("NAME: %s RECORD LENGTH: %d ", namelist[n]->d_name,
               namelist[n]->d_reclen);
        switch (namelist[n]->d_type) {
            case DT_UNKNOWN:
                puts("TYPE: unknown");
                break;
            case DT_FIFO:
                puts("TYPE: fifo");
                break;
            case DT_CHR:
                puts("TYPE: character device");
                break;
            case DT_DIR:
                puts("TYPE: directory");
                break;
            case DT_BLK:
                puts("TYPE: block device");
                break;
            case DT_REG:
                puts("TYPE: regular");
                break;
            case DT_LNK:
                puts("TYPE: link");
                break;
            case DT_SOCK:
                puts("TYPE: unix domain socket");
                break;
            case DT_WHT:
                puts("TYPE: whiteout");
                break;
        }
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}