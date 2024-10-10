#include <gtest/gtest.h>

// Declare the mock for the external function
extern "C" {
    #include "A/A.h"  // The function under test
    #include "B/B.h"  // dependency
    #include "fff.h"  // FFF mocking framework

    DEFINE_FFF_GLOBALS
    FAKE_VALUE_FUNC(int, B_function, int);
}

class ATest : public ::testing::Test {
protected:
    void SetUp() override {
        RESET_FAKE(B_function);
        FFF_RESET_HISTORY();
    }
};

// Test case for the process function
TEST_F(ATest, BMock) {
    // Setup the mock behavior
    B_function_fake.return_val = 5;

    // Call the process function and check the result
    EXPECT_EQ(process(3), 6);

    // Verify that the mock function was called with the expected parameter
    EXPECT_EQ(B_function_fake.call_count, 1);
    EXPECT_EQ(B_function_fake.arg0_val, 3);
}