#include <map>
#include <queue>
#include <vector>

#include <gtest/gtest.h>

#include "validator/types_check/has_validate.h"

namespace validator {

class HasValidateTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

class A {
public:
    void Validate() {}
};

class B {};

TEST_F(HasValidateTest, has_size_test) {
    EXPECT_TRUE(validator::has_validate_v<A>);
    EXPECT_FALSE(validator::has_validate_v<B>);
}

}  // namespace validator
