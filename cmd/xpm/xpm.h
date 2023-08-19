#ifndef _XPM_H
#define _XPM_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "x.h"

#ifndef _XOS_BUILD
#define XPM_MAGIC 0x1EF1D0BA
#else
#define XPM_MAGIC 0x075BCD15
#endif


struct x_pm_package_node {
    char* version;
};

struct x_pm_conf_main {
    char* name;
    char* version;
    char* pm_version;
    char* local_md5;
};

#endif
