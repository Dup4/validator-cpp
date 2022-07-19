#pragma once

#include "validator/validator.h"

namespace validator::test {

struct C {
    int a;
};

VALIDATOR_EXTERNAL_DECLARE_BEGIN(C)
VALIDATOR_EXTERNAL_DECLARE_FIELD(a)
VALIDATOR_EXTERNAL_DECLARE_END

}  // namespace validator::test
