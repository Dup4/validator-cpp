#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "validator/validator.h"

namespace validator::validate {

class IsNotEmptyTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsNotEmptyTest, is_not_empty_test) {
    struct A {
        std::string s;

        VALIDATOR_DECLARE_BEGIN
        VALIDATOR_DECLARE_FIELD(s, IsNotEmpty());
        VALIDATOR_DECLARE_END
    };

    A a;

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.isValidation);
        EXPECT_EQ(res.errorMessage, std::string("`s` is empty."));
    }
}

}  // namespace validator::validate
