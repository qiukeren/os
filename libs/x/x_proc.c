#include "x_proc.h"

void x_set_proc_title(char* fmt) {
#ifndef __APPLE__
    prctl(PR_SET_NAME, fmt);
#endif
}

void x_set_proc_title_va(char* fmt, ...) {
    char buf[256];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
#ifndef __APPLE__
    prctl(PR_SET_NAME, fmt);
#endif
}
