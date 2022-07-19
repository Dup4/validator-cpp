#ifndef VALIDATOR_VALIDATE_LENGTH_H
#define VALIDATOR_VALIDATE_LENGTH_H

#include <cstddef>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/result_utility.h"
#include "../internal/validator.h"
#include "../types_check/has_length.h"

namespace validator {

class Length : public OptionsBaseBuilder {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    Length() = delete;
    template <typename... Opt>
    Length(size_t min_len, size_t max_len, Opt&&... opts) : min_len_(min_len), max_len_(max_len) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto [ok, actual_value] = validate(t);
        if (ok) {
            return Result::OK();
        }

        std::string error_message_pattern =
                "The length of `$field_name` is not valid. The range of lengths is [$min_length, $max_length], but actual is $actual_length.";
        std::map<std::string, std::string> replace_map = {
                {"$field_name", options_.field_name.value_or("")},
                {"$min_length", std::to_string(min_len_)},
                {"$max_length", std::to_string(max_len_)},
                {"$actual_length", std::to_string(actual_value)},
        };

        std::string error_message = ResultUtility::GenerateErrorMessage(
                options_.error_message_pattern.value_or(error_message_pattern), replace_map);

        auto res = Result::Builder(Result::ErrorCode::ValidateError).WithErrorMessage(error_message).Build();
        RESULT_DIRECT_RETURN(res);
    }

private:
    template <typename T>
    std::tuple<bool, size_t> validate(const T& t) {
        static_assert(has_length_v<T>, "T must have length() method");

        auto ok = t.length() >= min_len_ && t.length() <= max_len_;
        return std::make_tuple(ok, t.length());
    }

private:
    Options options_;
    size_t min_len_;
    size_t max_len_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_LENGTH_H
