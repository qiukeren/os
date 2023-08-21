#include <gtest/gtest.h>
#include "x.h"
#include "xlog.h"

TEST(x_flag, test_encode_readu32) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15};
    uint32_t s = x_read_uint32(p);
    EXPECT_EQ(s, 0x275BCD15);
}

TEST(x_flag, test_encode_uint32_t) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15};
    X_ENCODE_STRING* t = x_write_uint32_to_chars(0x275BCD15);
    EXPECT_EQ(t->size, 4);
    LOG_DEBUG("x_write_uint32_to_chars %x %x", t->data[0], p[0]);
    EXPECT_EQ(t->data[0], p[0]);
    EXPECT_EQ(t->data[0], 0x27);
    LOG_DEBUG("x_write_uint32_to_chars %x %x", t->data[1], p[1]);
    EXPECT_EQ(t->data[1], p[1]);
    EXPECT_EQ(t->data[1], 0x5b);
    LOG_DEBUG("x_write_uint32_to_chars %x %x", t->data[2], p[2]);
    EXPECT_EQ(t->data[2], p[2]);
    EXPECT_EQ(t->data[2], 0xcd);
    LOG_DEBUG("x_write_uint32_to_chars %x %x", t->data[3], p[3]);
    EXPECT_EQ(t->data[3], p[3]);
    EXPECT_EQ(t->data[3], 0x15);
    x_free_encode_bytes(t);
}

TEST(x_flag, test_encode_uint64_t) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15, 0x11, 0x22, 0x33, 0x44};

    X_ENCODE_STRING* t = x_write_uint64_to_chars(0x275BCD1511223344);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[0], p[0]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[1], p[1]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[2], p[2]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[3], p[3]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[4], p[4]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[5], p[5]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[6], p[6]);
    LOG_DEBUG("x_write_uint64_to_chars %x %x", t->data[7], p[7]);

    EXPECT_EQ(t->size, 8);
    EXPECT_EQ(t->data[0], p[0]);
    EXPECT_EQ(t->data[0], 0x27);
    EXPECT_EQ(t->data[1], p[1]);
    EXPECT_EQ(t->data[1], 0x5b);
    EXPECT_EQ(t->data[2], p[2]);
    EXPECT_EQ(t->data[2], 0xcd);
    EXPECT_EQ(t->data[3], p[3]);
    EXPECT_EQ(t->data[3], 0x15);
    EXPECT_EQ(t->data[4], p[4]);
    EXPECT_EQ(t->data[4], 0x11);
    EXPECT_EQ(t->data[5], p[5]);
    EXPECT_EQ(t->data[5], 0x22);
    EXPECT_EQ(t->data[6], p[6]);
    EXPECT_EQ(t->data[6], 0x33);
    EXPECT_EQ(t->data[7], p[7]);
    EXPECT_EQ(t->data[7], 0x44);
    // x_free_encode_bytes(&t);
}

TEST(x_flag, test_encode_readu64) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15, 0x11, 0x22, 0x33, 0x44};
    uint64_t s = x_read_uint64(p);
    EXPECT_EQ(s, 0x275BCD1511223344);
}

TEST(x_flag, test_encode_readu3264_move) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15, 0x1, 0x2, 0x3,
                   0x4,  0x5,  0x6,  0x7,  0x8, 0x9};
    uint8_t* ptr = p;
    uint32_t s32 = x_read_and_move_uint32(&ptr);
    EXPECT_EQ(s32, 0x275BCD15);
    uint64_t s64 = x_read_and_move_uint64(&ptr);
    EXPECT_EQ(s64, 0x0102030405060708);
}

TEST(x_flag, test_encode_readchars) {
    uint8_t f[] = {'e', '5', '7', '9', '4', '1', 'f', 'f', '9', '0', '0',
                   '0', 'a', 'e', 'd', 'b', '4', '4', 'e', 'b', '2', 'f',
                   'a', '1', '3', 'f', '6', 'e', '3', 'e', '3', 'c', '1',
                   '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
    uint8_t* p = f;
    {
        char target[33];
        x_read_chars(p, 32, target);
        p += 32;
        target[32] = '\0';
        EXPECT_STREQ("e57941ff9000aedb44eb2fa13f6e3e3c", target);
    }
    {
        char target2[5];
        x_read_chars(p, 4, target2);
        *p = *p + 4;
        target2[4] = '\0';
        EXPECT_STREQ("1234", target2);
    }
}

TEST(x_flag, test_encode_read_and_move_chars) {
    uint8_t f[] = {'e', '5', '7', '9', '4', '1', 'f', 'f', '9', '0', '0',
                   '0', 'a', 'e', 'd', 'b', '4', '4', 'e', 'b', '2', 'f',
                   'a', '1', '3', 'f', '6', 'e', '3', 'e', '3', 'c', '1',
                   '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
    uint8_t* p = f;
    {
        char target[33];
        x_read_move_chars(&p, 32, target);
        target[32] = '\0';
        EXPECT_STREQ("e57941ff9000aedb44eb2fa13f6e3e3c", target);
    }
    {
        char target2[5];
        x_read_move_chars(&p, 4, target2);
        target2[4] = '\0';
        EXPECT_STREQ("1234", target2);
    }
}
