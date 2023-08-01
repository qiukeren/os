#pragma once
#ifndef _X_KERNEL_LOG_H
#define _X_KERNEL_LOG_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void x_kernel_log(const unsigned int tag, const char* msg);
void x_kernel_log_warn(const char* msg);
void x_kernel_log_info(const char* msg);
void x_kernel_log_debug(const char* msg);

#endif
