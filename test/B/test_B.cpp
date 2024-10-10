#include <gtest/gtest.h>

// Declare the mock for the external function
extern "C" {
    #include "B/B.h"  // The function under test
    #include "C/C.h"  // dependency
    #include "fff.h"  // FFF mocking framework

    DEFINE_FFF_GLOBALS
    FAKE_VALUE_FUNC(int, C_function, int);
}

class BTest : public ::testing::Test {
protected:
    void SetUp() override {
        RESET_FAKE(C_function);
        FFF_RESET_HISTORY();
    }
};

// Test case for the process function
TEST_F(BTest, CMock) {
    // Setup the mock behavior
    C_function_fake.return_val = 5;

    // Call the process function and check the result
    EXPECT_EQ(B_function(8), 10);

    // Verify that the mock function was called with the expected parameter
    EXPECT_EQ(C_function_fake.call_count, 1);
    EXPECT_EQ(C_function_fake.arg0_val, 8);
}