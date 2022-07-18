#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "validator/validate/validate_nested.h"
#include "validator/validator.h"

namespace validator {

class ValidatorTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

struct A {
    int a;
    std::string s;
    std::vector<int> t;

    VALIDATOR_DECLARE_BEGIN
    VALIDATOR_DECLARE_FIELD(a);
    VALIDATOR_DECLARE_FIELD(s, MinLength(1), MaxLength(10), Length(1, 10));
    VALIDATOR_DECLARE_FIELD(t, Size(0, 10, Size::WithErrorMessagePattern("size error")));
    VALIDATOR_DECLARE_END
};

struct B {
    A a;

    VALIDATOR_DECLARE_BEGIN
    VALIDATOR_DECLARE_FIELD(a, ValidateNested());
    VALIDATOR_DECLARE_END
};

TEST_F(ValidatorTest, validator_test) {
    A a;

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.IsValidation);
        EXPECT_EQ(res.ErrorMessage, std::string("`s` is to short. Min length is 1, but actual is 0."));
    }

    {
        a.s = "12345678901";
        auto res = a.Validate();
        EXPECT_FALSE(res.IsValidation);
        EXPECT_EQ(res.ErrorMessage, std::string("`s` is to long. Max length is 10, but actual is 11."));
    }

    {
        a.s = "123";
        auto res = a.Validate();
        EXPECT_TRUE(res.IsValidation);
    }

    {
        a.t = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        auto res = a.Validate();
        EXPECT_FALSE(res.IsValidation);
        EXPECT_EQ(res.ErrorMessage, std::string("size error"));
    }
}

TEST_F(ValidatorTest, validator_nested_test) {
    B b;

    {
        auto res = b.Validate();
        EXPECT_FALSE(res.IsValidation);
        EXPECT_EQ(res.ErrorMessage, std::string("`s` is to short. Min length is 1, but actual is 0."));
    }
}

}  // namespace validator
