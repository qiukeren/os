#include <gtest/gtest.h>

int add(int a, int b) { 
    return a + b; 
}


TEST(testCase, test0) { 
    EXPECT_EQ(add(8, 12), 30);
}

TEST(testCase, test1) {
    EXPECT_EQ(add(8, 12), 20);
}

TEST(testCase, test2) {
    EXPECT_EQ(add(8, 12), 30);
}

TEST(testCase, test3) {
    EXPECT_EQ(add(8, 12), 20);
}

TEST(testCase, test4) {
    EXPECT_EQ(add(8, 12), 30);
}

TEST(testCase, test5) {
    EXPECT_EQ(add(8, 12), 30);
}
