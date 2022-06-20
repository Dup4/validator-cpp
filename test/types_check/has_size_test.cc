#include <map>
#include <queue>
#include <vector>

#include <gtest/gtest.h>

#include "validator/types_check/has_size.h"

namespace validator {

class HasSizeTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(HasSizeTest, has_size_test) {
    EXPECT_TRUE(validator::has_size_v<std::string>);
    EXPECT_TRUE(validator::has_size_v<std::vector<int>>);
    EXPECT_TRUE(validator::has_size_v<std::set<int>>);
    EXPECT_TRUE(validator::has_size_v<std::queue<int>>);

    EXPECT_FALSE(validator::has_size_v<int>);
    EXPECT_FALSE(validator::has_size_v<char>);
}

}  // namespace validator
