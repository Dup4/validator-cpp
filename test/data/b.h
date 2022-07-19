#pragma once

#include "validator/validator.h"

#include "./a.h"

namespace validator::test {

struct B {
    A a;

    VALIDATOR_DECLARE_BEGIN(B)
    VALIDATOR_DECLARE_FIELD(a, ValidateNested())
    VALIDATOR_DECLARE_END
};

}  // namespace validator::test
