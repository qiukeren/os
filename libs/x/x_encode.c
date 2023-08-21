#include "x_encode.h"

X_ENCODE_STRING* x_write_uint32_to_chars(uint32_t t) {
    X_ENCODE_STRING* dest = x_new_encode_bytes(4);
    
    uint8_t b3 = (uint8_t)(t >> 24);
    uint8_t b2 = (uint8_t)(t >> 16);
    uint8_t b1 = (uint8_t)(t >> 8);
    uint8_t b0 = (uint8_t)(t >> 0);
    // uint8_t res[4] = {b3, b2, b1, b0};
    dest->size = 4;
    dest->data = malloc(dest->size);
    (dest->data)[0] = b3;
    (dest->data)[1] = b2;
    (dest->data)[2] = b1;
    (dest->data)[3] = b0;
    return dest;
}

X_ENCODE_STRING* x_write_uint64_to_chars(uint64_t t) {
    X_ENCODE_STRING* dest = x_new_encode_bytes(8);

    char b7 = (uint64_t)(t >> 56);
    char b6 = (uint64_t)(t >> 48);
    char b5 = (uint64_t)(t >> 40);
    char b4 = (uint64_t)(t >> 32);
    char b3 = (uint64_t)(t >> 24);
    char b2 = (uint64_t)(t >> 16);
    char b1 = (uint64_t)(t >> 8);
    char b0 = (uint64_t)(t >> 0);
    // char res[8] = {b7, b6, b5, b4, b3, b2, b1, b0};
    // return res;
    dest->size = 8;
    dest->data = malloc(dest->size);
    (dest->data)[0] = b7;
    (dest->data)[1] = b6;
    (dest->data)[2] = b5;
    (dest->data)[3] = b4;
    (dest->data)[4] = b3;
    (dest->data)[5] = b2;
    (dest->data)[6] = b1;
    (dest->data)[7] = b0;
    return dest;
}

X_ENCODE_STRING* x_new_encode_bytes(uint32_t size) {
    X_ENCODE_STRING* dest = malloc(sizeof(X_ENCODE_STRING));
    dest->size = size;
    dest->data = malloc(size);
    return dest;
}
void x_free_encode_bytes(X_ENCODE_STRING* x) {
    if (x->data != NULL) {
        free(x->data);
    }
    free(x);
}