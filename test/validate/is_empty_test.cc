#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "validator/validate/is_empty.h"
#include "validator/validator.h"

namespace validator {

namespace is_empty_test {

struct A {
    std::string s;

    VALIDATOR_DECLARE_BEGIN(A)
    VALIDATOR_DECLARE_FIELD(s, IsEmpty())
    VALIDATOR_DECLARE_END
};

}  // namespace is_empty_test

class IsEmptyTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsEmptyTest, is_empty_test) {
    using namespace is_empty_test;

    A a;
    a.s = "d";

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("`s` is not empty."));
    }
}

}  // namespace validator
