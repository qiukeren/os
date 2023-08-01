#ifndef _X_PROC_H
#define _X_PROC_H
#include <sys/prctl.h>
void x_set_proc_title(char* fmt);
void x_set_proc_title_va(char* fmt, ...);
#endif
