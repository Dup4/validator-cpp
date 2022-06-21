#ifndef VALIDATOR_VALIDATE_IS_NOT_EMPTY_H
#define VALIDATOR_VALIDATE_IS_NOT_EMPTY_H

#include <cstddef>
#include <utility>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/validator.h"
#include "../types_check/has_empty.h"

namespace validator {

class IsNotEmpty : public OptionsBaseBuilder {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    template <typename... Opt>
    IsNotEmpty(Opt&&... opts) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto ok = validate(t);

        if (ok) {
            return ValidResult;
        }

        std::string error_message_pattern = "`$field_name` is empty.";

        std::map<std::string, std::string> replace_map = {
                {"$field_name", options_.field_name.value_or("")},
        };

        std::string error_message =
                GenerateErrorMessage(options_.error_message_pattern.value_or(error_message_pattern), replace_map);

        return ResultBuilder().WithIsValidation(false).WithErrorMessage(error_message).Build();
    }

private:
    template <typename T>
    bool validate(const T& t) {
        static_assert(has_empty_v<T>, "T must have empty() method");

        auto ok = !t.empty();
        return ok;
    }

private:
    Options options_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_IS_NOT_EMPTY_H
