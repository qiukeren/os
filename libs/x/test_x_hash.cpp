#include <gtest/gtest.h>
#include "x.h"

TEST(x, test_hash_md5_xxxa111) {
    char expRes[] = "f2329fa52888c1608408d259436f9ef2";
    {
        char t[] = "test";
        x_mkdir(t, 0755);
    }
    {
        char cmd[] = "echo 'xxxa111' > test/test_hash_md5_xxxa111";
        x_command_check(cmd);
    }
    {
        char f[] = "test/test_hash_md5_xxxa111";
        FILE* a = fopen(f, "r");
        char m[33];
        x_md5_sum(a, m);

        EXPECT_STREQ(m, expRes);
    }
}
