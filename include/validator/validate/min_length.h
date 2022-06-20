#ifndef VALIDATOR_VALIDATE_MIN_LENGTH_H
#define VALIDATOR_VALIDATE_MIN_LENGTH_H

#include <cstddef>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/validator.h"
#include "../types_check/has_length.h"

namespace validator {

class MinLength : public OptionsBaseBuilder {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    MinLength() = delete;
    template <typename... Opt>
    MinLength(size_t len, Opt&&... opts) : len_(len) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto [ok, actual_value] = validate(t);

        if (ok) {
            return ValidResult;
        }

        std::string error_message_pattern =
                "`$field_name` is to short. Min length is $min_length, but actual is $actual_length.";
        std::map<std::string, std::string> replace_map = {
                {"$field_name", options_.field_name.value_or("")},
                {"$min_length", std::to_string(len_)},
                {"$actual_length", std::to_string(actual_value)},
        };

        std::string error_message =
                GenerateErrorMessage(options_.error_message_pattern.value_or(error_message_pattern), replace_map);

        return ResultBuilder().WithIsValidation(false).WithErrorMessage(error_message).Build();
    }

private:
    template <typename T>
    std::tuple<bool, size_t> validate(const T& t) {
        static_assert(has_length_v<T>, "T must have length() method");

        auto ok = t.length() >= len_;
        return std::make_tuple(ok, t.length());
    }

private:
    Options options_;
    size_t len_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_MIN_LENGTH_H
