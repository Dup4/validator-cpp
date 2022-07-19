#pragma once

#include <string>
#include <vector>

#include "validator/validator.h"

namespace validator::test {

struct A {
    int a;
    std::string s;
    std::vector<int> t;

    VALIDATOR_DECLARE_BEGIN(A)
    VALIDATOR_DECLARE_FIELD(a)
    VALIDATOR_DECLARE_FIELD(s, MinLength(1), MaxLength(10), Length(1, 10))
    VALIDATOR_DECLARE_FIELD(t, Size(0, 10, Size::WithErrorMessagePattern("size error")))
    VALIDATOR_DECLARE_END
};

}  // namespace validator::test
