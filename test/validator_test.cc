#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

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

    VALIDATOR_BEGIN
    VALIDATOR_DECLARE(a);
    VALIDATOR_DECLARE(s, MinLength(1), MaxLength(10), Length(1, 10));
    // VALIDATOR_DECLARE(t, Length(0, 10))
    VALIDATOR_END
};

TEST_F(ValidatorTest, validator_test) {
    A a;

    {
        auto res = a.Validate();
        EXPECT_FALSE(res.isValidation);
        SNAPSHOT(res.errorMessage);
    }

    {
        a.s = "12345678901";
        auto res = a.Validate();
        EXPECT_FALSE(res.isValidation);
        SNAPSHOT(res.errorMessage);
    }

    {
        a.s = "123";
        auto res = a.Validate();
        EXPECT_TRUE(res.isValidation);
    }

    // {
    //     a.t = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    //     auto res = a.Validate();
    //     EXPECT_FALSE(res.isValidation);
    // }
}

}  // namespace validator
