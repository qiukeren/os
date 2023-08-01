#include <gtest/gtest.h>

#include "x.h"
using namespace std;

TEST(x, test_hash_md5_xxxa111) {
    string expRes = "f2329fa52888c1608408d259436f9ef2";
    x_mkdir("test", 0755);
    x_command_check("echo 'xxxa111' > test/test_hash_md5_xxxa111");
    FILE* a = fopen("test/test_hash_md5_xxxa111", "r");
    char m[33];
    x_md5_sum(a, m);
    EXPECT_STREQ(m, expRes.c_str());
}
