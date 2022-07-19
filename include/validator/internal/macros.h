#ifndef VALIDATOR_INTERNAL_MACROS_H
#define VALIDATOR_INTERNAL_MACROS_H

#include "../types_check/has_internal_validate.h"
#include "./inject_entrance.h"
#include "./result.h"
#include "./validator.h"

#define VALIDATOR_DECLARE_BEGIN(Struct)                      \
    friend class ::validator::InjectEntrance;                \
    friend class ::validator::has_internal_validate<Struct>; \
                                                             \
private:                                                     \
    Result __Validator_Validate() const {
//
#define VALIDATOR_DECLARE_END          \
    return ::validator::Result::OK();  \
    }                                  \
                                       \
public:                                \
    Result Validate() const {          \
        return __Validator_Validate(); \
    }

#define VALIDATOR_DECLARE_FIELD(field, ...)                                                    \
    {                                                                                          \
        auto res = ::validator::Validator::ExecuteMultiValidate(field, #field, ##__VA_ARGS__); \
        if (!res.IsOK()) {                                                                     \
            return res;                                                                        \
        }                                                                                      \
    }

#endif  // VALIDATOR_INTERNAL_MACROS_H
