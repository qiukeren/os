#include "x_sys.h"

void x_sys_print_build_version() {
    struct x_sys_version sqlite_v = x_sys_sqlite_version();
    printf("%s->%s\n", sqlite_v.name, sqlite_v.version);
}

struct x_sys_version x_sys_sqlite_version() {
    char str[30];
    snprintf(str, 30, "%s", sqlite3_libversion());
    struct x_sys_version v = {"sqlite", str};
    return v;
}