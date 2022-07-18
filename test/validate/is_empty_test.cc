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

        VALIDATOR_DECLARE_BEGIN
        VALIDATOR_DECLARE_FIELD(s, IsEmpty());
        VALIDATOR_DECLARE_END
    };

    A a;
    a.s = "d";

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.IsValidation);
        EXPECT_EQ(res.ErrorMessage, std::string("`s` is not empty."));
    }
}

}  // namespace validator::validate
