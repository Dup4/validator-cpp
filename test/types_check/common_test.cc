#include <map>
#include <queue>
#include <vector>

#include <gtest/gtest.h>

#include "validator/types_check/common.h"

namespace validator::types_check {

class CommonTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(CommonTest, common_test) {
    EXPECT_FALSE(false_v<int>);
    EXPECT_FALSE(false_v<std::string>);
}

}  // namespace validator::types_check
