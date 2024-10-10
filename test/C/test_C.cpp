#include <gtest/gtest.h>

// Declare the mock for the external function
extern "C" {
    #include "C/C.h"  // The function under test
}

// Test case for the process function
TEST(CTest, CFunction) {
    int result = C_function(5);    // 调用C_function
    ASSERT_EQ(result, 50);         // 期望结果是5 * 10
}