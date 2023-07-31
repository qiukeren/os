#ifndef _X_SYS_H

#define _X_SYS_H

#include "sqlite3.h"
#include <stdio.h>

struct x_sys_version{
    char*name;
    char *version;
};

void x_sys_print_build_version();
struct x_sys_version x_sys_sqlite_version();
#endif
