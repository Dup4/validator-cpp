#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "validator/validate/is_empty.h"
#include "validator/validator.h"

namespace validator::validate {

class IsEmptyTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsEmptyTest, is_empty_test) {
    struct A {
        std::string s;

        VALIDATOR_BEGIN
        VALIDATOR_DECLARE(s, IsEmpty());
        VALIDATOR_END
    };

    A a;

    a.s = "d";

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.isValidation);
        EXPECT_EQ(res.errorMessage, std::string("`s` is not empty."));
    }
}

}  // namespace validator::validate
