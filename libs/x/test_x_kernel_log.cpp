#include <gtest/gtest.h>

int add(int a, int b) { 
    return a + b; 
}


TEST(x, startCase) { 
    EXPECT_EQ(add(8, 12), 20);
}
