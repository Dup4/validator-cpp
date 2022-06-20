#ifndef VALIDATOR_VALIDATE_VALIDATE_NESTED_H
#define VALIDATOR_VALIDATE_VALIDATE_NESTED_H

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/validator.h"
#include "../types_check/has_validate.h"

namespace validator {

class ValidateNested {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    ValidateNested() = default;

    template <typename T>
    Result Validate(const T& t) {
        static_assert(has_validate_v<T>, "T must have Validate() method");
        return t.Validate();
    }

private:
    Options options_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_VALIDATE_NESTED_H
