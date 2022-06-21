#include <map>
#include <queue>
#include <vector>

#include <gtest/gtest.h>

#include "validator/types_check/has_empty.h"

namespace validator {

class HasEmptyTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(HasEmptyTest, has_empty_test) {
    EXPECT_TRUE(validator::has_empty_v<std::string>);
    EXPECT_TRUE(validator::has_empty_v<std::vector<int>>);
    EXPECT_TRUE(validator::has_empty_v<std::set<int>>);
    EXPECT_TRUE(validator::has_empty_v<std::queue<int>>);

    EXPECT_FALSE(validator::has_empty_v<int>);
    EXPECT_FALSE(validator::has_empty_v<char>);
}

}  // namespace validator
