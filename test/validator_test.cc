#include <gtest/gtest.h>

#include "validator/validator.h"

class ValidatorTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(ValidatorTest, validator_test) {
    EXPECT_EQ("Hello World", "Hello World");
}
