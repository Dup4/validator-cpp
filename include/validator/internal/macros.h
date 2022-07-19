#ifndef VALIDATOR_INTERNAL_MACROS_H
#define VALIDATOR_INTERNAL_MACROS_H

#include "./result.h"
#include "./validator.h"

namespace validator {

#define VALIDATOR_DECLARE_BEGIN \
                                \
public:                         \
    Result Validate() const {
#define VALIDATOR_DECLARE_END         \
    return ::validator::Result::OK(); \
    }

#define VALIDATOR_DECLARE_FIELD(field, ...)                                                    \
    {                                                                                          \
        auto res = ::validator::Validator::ExecuteMultiValidate(field, #field, ##__VA_ARGS__); \
        if (!res.IsOK()) {                                                                     \
            return res;                                                                        \
        }                                                                                      \
    }

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_MACROS_H
