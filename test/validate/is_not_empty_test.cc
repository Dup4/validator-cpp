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

        VALIDATOR_DECLARE_BEGIN(A)
        VALIDATOR_DECLARE_FIELD(s, IsNotEmpty());
        VALIDATOR_DECLARE_END
    };

    A a;

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("`s` is empty."));
    }
}

}  // namespace validator::validate
