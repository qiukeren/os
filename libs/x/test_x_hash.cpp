#include <gtest/gtest.h>
#include "x_command.h"


TEST(testCase, command_check_ls_not_exist) {
    char* cmd = "ls_not_exist_command > /dev/null 2>&1";
    EXPECT_EQ(x_command_check(cmd), false);
}

TEST(testCase, test_hash_md5_xxxa111) {
    x_mkdir("test/")
    x_command_check("echo 'xxxa111' > test/test_hash_md5_xxxa111")
    EXPECT_EQ(a == NULL, true);
}
