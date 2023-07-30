#include <stdarg.h>
#include <stdio.h>
#include <sys/prctl.h>

void x_set_proc_title(char* fmt) {
    prctl(PR_SET_NAME, fmt);
}

void x_set_proc_title_va(char* fmt, ...) {
    char buf[256];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    prctl(PR_SET_NAME, fmt);
}
