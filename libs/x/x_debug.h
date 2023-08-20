#pragma once
#ifndef _X_DEBUG
#define _X_DEBUG
#include <stdint.h>
#include <stdio.h>

void x_debug_print_file_content(char* filename);
void dump_hex(const uint8_t* buf, uint32_t size, uint32_t number);

#endif
