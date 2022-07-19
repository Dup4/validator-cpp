#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "validator/validate/validate_nested.h"
#include "validator/validator.h"

#include "./data/a.h"
#include "./data/b.h"
#include "./data/c.h"

namespace validator {

using namespace test;

class ValidatorTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(ValidatorTest, validator_test) {
    A a;

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("`s` is to short. Min length is 1, but actual is 0."));
    }

    {
        auto res = Validator::Validate(a);
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("`s` is to short. Min length is 1, but actual is 0."));
    }

    {
        a.s = "12345678901";
        auto res = a.Validate();
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("`s` is to long. Max length is 10, but actual is 11."));
    }

    {
        a.s = "123";
        auto res = a.Validate();
        EXPECT_TRUE(res.IsOK());
    }

    {
        a.t = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        auto res = a.Validate();
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("size error"));
    }
}

TEST_F(ValidatorTest, validator_nested_test) {
    B b;

    {
        auto res = b.Validate();
        EXPECT_FALSE(res.IsOK());
        EXPECT_EQ(res.Message(), std::string("`s` is to short. Min length is 1, but actual is 0."));
    }
}

TEST_F(ValidatorTest, validator_external_test) {
    C c;

    {
        auto res = Validator::Validate(c);
        EXPECT_TRUE(res.IsOK());
    }
}

}  // namespace validator
