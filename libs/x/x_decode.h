#ifndef _X_DECODE_H
#define _X_DECODE_H

#include <stdint.h>
#include <string.h>
#include "xlog.h"

uint32_t x_read_uint32(uint8_t* pointer);
uint64_t x_read_uint64(uint8_t* pointer);

uint32_t x_read_and_move_uint32(uint8_t** pointer);
uint64_t x_read_and_move_uint64(uint8_t** pointer);

void x_read_chars(uint8_t* pointer, int size, char* target);
void x_read_move_chars(uint8_t** pointer, int size, char* target);

#endif