#include <x_decode.h>

uint32_t x_read_uint32(uint8_t* pointer) {
    uint32_t i32 = 0;
    for (int i = 3; i >= 0; i--) {
        i32 = i32 + ((uint32_t)*pointer << (8 * i));
        pointer++;
    }
    return i32;
}

uint32_t x_read_and_move_uint32(uint8_t** pointer) {
    uint32_t i32 = 0;
    for (int i = 3; i >= 0; i--) {
        LOG_TRACE("%x", **pointer);
        i32 = i32 + (((uint32_t)(**pointer)) << (8 * i));
        (*pointer)++;
    }
    return i32;
}

uint64_t x_read_uint64(uint8_t* pointer) {
    uint64_t i64 = 0;
    for (int i = 7; i >= 0; i--) {
        LOG_TRACE("%x", *pointer);
        i64 = i64 + ((uint64_t)*pointer << (8 * i));
        pointer++;
    }
    return i64;
}

uint64_t x_read_and_move_uint64(uint8_t** pointer) {
    uint64_t i64 = 0;
    for (int i = 7; i >= 0; i--) {
        LOG_TRACE("%x", **pointer);
        i64 = i64 + ((uint64_t)(**pointer) << (8 * i));
        (*pointer)++;
    }
    return i64;
}

void x_read_chars(uint8_t* pointer, int size, char* target) {
    strncpy(target, (char*)pointer, size);
}

void x_read_move_chars(uint8_t** pointer, int size, char* target) {
    strncpy(target, (char*)*pointer, size);
    (*pointer) += size;
}
