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
        RESULT_OK_OR_RETURN(res);                                                              \
    }

#define VALIDATOR_EXTERNAL_DECLARE_BEGIN(Struct) Result __ValidatorExternal_Validate([[maybe_unused]] const Struct& s) {
//
#define VALIDATOR_EXTERNAL_DECLARE_END \
    return ::validator::Result::OK();  \
    }

#define VALIDATOR_EXTERNAL_DECLARE_FIELD(field, ...)                                             \
    {                                                                                            \
        auto res = ::validator::Validator::ExecuteMultiValidate(s.field, #field, ##__VA_ARGS__); \
        RESULT_OK_OR_RETURN(res);                                                                \
    }

#endif  // VALIDATOR_INTERNAL_MACROS_H
