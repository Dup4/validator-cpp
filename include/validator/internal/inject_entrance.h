#ifndef VALIDATOR_INTERNAL_INJECT_ENTRANCE_H
#define VALIDATOR_INTERNAL_INJECT_ENTRANCE_H

#include "../types_check/common.h"
#include "../types_check/has_external_validate.h"
#include "../types_check/has_internal_validate.h"
#include "./result.h"

namespace validator {

class InjectEntrance {
public:
    template <typename T>
    static Result Validate(const T& t) {
        if constexpr (has_internal_validate_v<T>) {
            return t.__Validator_Validate();
        } else if constexpr (has_external_validate_v<T>) {
            return __ValidatorExternal_Validate(t);
        } else {
            static_assert(false_v<T>, "No Validate method found");
        }
    }
};

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_INJECT_ENTRANCE_H
