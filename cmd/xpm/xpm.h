#ifndef _XPM_H
#define _XPM_H

#include <stdio.h>
#include "x.h"

struct x_pm_package_node {
    char* version;
};

struct x_pm_conf_main {
    char* name;
    char* version;
    char* pm_version;
    char* local_md5;
};

void xpm_init();

#endif
