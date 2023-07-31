#ifndef _XPM_H
#define _XPM_H

#include <stdio.h>
#include "x_paths.h"
#include "yaml.h"

#define XPM_PACKAGE_LIST_FILE "xpm.yml"

struct x_pm_package_node {
    char* name;
    char* version;
};

struct x_pm_conf_main {
    char* name;
    char* version;
    char* pm_version;
    char* local_md5;
};

#endif
