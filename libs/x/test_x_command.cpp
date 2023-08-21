#include <gtest/gtest.h>
#include "x.h"

TEST(x, command_check_ls) {
    char cmd[] = "ls > /dev/null 2>&1";
    EXPECT_EQ(x_command_check(cmd), true);
}

TEST(x, command_check_ls_not_exist) {
    char cmd[] = "ls_not_exist_command > /dev/null 2>&1";
    EXPECT_EQ(x_command_check(cmd), false);
}

TEST(x, command_open_not_exist_null) {
    FILE* a = fopen("file_not_exist", "r");
    EXPECT_EQ(a == NULL, true);
}