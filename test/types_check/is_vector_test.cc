#include <gtest/gtest.h>
#include <vector>

#include "validator/types_check/is_vector.h"

namespace validator {

class IsVectorTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsVectorTest, is_vector_test) {
    EXPECT_TRUE(validator::is_vector_v<std::vector<int>>);
    EXPECT_TRUE(validator::is_vector_v<std::vector<std::string>>);
    EXPECT_TRUE(validator::is_vector_v<std::vector<std::vector<int>>>);

    EXPECT_FALSE(validator::is_vector_v<int>);
}

}  // namespace validator
