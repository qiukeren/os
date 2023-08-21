#ifndef _X_ENCODE_H
#define _X_ENCODE_H

#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t size;
    uint8_t* data;
} X_ENCODE_STRING;

X_ENCODE_STRING* x_write_uint32_to_chars(uint32_t t);
X_ENCODE_STRING* x_write_uint64_to_chars(uint64_t t);

X_ENCODE_STRING* x_new_encode_bytes(uint32_t size);
void x_free_encode_bytes(X_ENCODE_STRING*);

#endif