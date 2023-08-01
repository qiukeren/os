#ifndef _X_PROC_H
#define _X_PROC_H

#ifndef __APPLE__
#include <sys/prctl.h>
#endif

#include <stdarg.h>
#include <stdio.h>
void x_set_proc_title(char* fmt);
void x_set_proc_title_va(char* fmt, ...);

#endif
