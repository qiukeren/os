#include <gtest/gtest.h>
#include "xlog.h"
#include "x.h"

TEST(x_flag, test_encode_readu32) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15};
    uint32_t s = x_read_uint32(p);
    EXPECT_EQ(s, 0x275BCD15);
}

TEST(x_flag, test_encode_readu64) {
    uint8_t p[] = {0x27, 0x5b, 0xcd, 0x15, 0x01, 0x02, 0x03, 0x04};
    uint64_t s = x_read_uint64(p);
    EXPECT_EQ(s, 0x275BCD1501020304);
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
