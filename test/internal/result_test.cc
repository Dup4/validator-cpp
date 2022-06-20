#include <map>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

#include "validator/internal/result.h"

namespace validator {

class ResultTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(ResultTest, generate_error_message_test) {
    {
        std::string error_message_pattern = "";
        std::map<std::string, std::string> replace_map;
        EXPECT_EQ(GenerateErrorMessage(error_message_pattern, replace_map), "");
    }

    {
        std::string error_message_pattern = "test";
        std::map<std::string, std::string> replace_map;
        EXPECT_EQ(GenerateErrorMessage(error_message_pattern, replace_map), "test");
    }

    {
        std::string error_message_pattern = "test $value 222";
        std::map<std::string, std::string> replace_map = {
                {"$value", "123"},
        };
        EXPECT_EQ(GenerateErrorMessage(error_message_pattern, replace_map), "test 123 222");
    }
}

}  // namespace validator
