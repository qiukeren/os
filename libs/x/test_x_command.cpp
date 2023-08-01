#include <gtest/gtest.h>
#include "x_command.h"

TEST(testCase, command_check_ls) { 
    EXPECT_EQ(x_command_check("ls"), true);
}

TEST(testCase, command_check_ls_not_exist) { 
    EXPECT_EQ(x_command_check("ls_not_exist_command"), false);
}