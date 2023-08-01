//
// Created by qkr on 23-7-29.
//

#include "x_kernel_log.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
 #include <string.h>

void x_kernel_log(const unsigned int tag, const char* msg) {
    int fd_kmsg = open("/dev/kmsg", O_WRONLY);
    if (fd_kmsg == -1) {
        char* e = strerror(errno);
        puts(e);
        return;
    }
    FILE* f_kmsg = fdopen(fd_kmsg, "w");
    fprintf(f_kmsg, "<%u>%s", tag, msg);
    fclose(f_kmsg);  // closes the underlying fd_kmsg as well
}

void x_kernel_log_warn(const char* msg) {
    x_kernel_log(4, msg);
}

void x_kernel_log_info(const char* msg) {
    x_kernel_log(6, msg);
}

void x_kernel_log_debug(const char* msg) {
    x_kernel_log(7, msg);
}
