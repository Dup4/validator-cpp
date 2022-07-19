#ifndef VALIDATOR_VALIDATE_MIN_SIZE_H
#define VALIDATOR_VALIDATE_MIN_SIZE_H

#include <cstddef>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/result_utility.h"
#include "../internal/validator.h"
#include "../types_check/has_size.h"

namespace validator {

class MinSize : public OptionsBaseBuilder {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    MinSize() = delete;
    template <typename... Opt>
    MinSize(size_t size, Opt&&... opts) : size_(size) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto [ok, actual_value] = validate(t);
        if (ok) {
            return Result::OK();
        }

        std::string error_message_pattern =
                "`$field_name` is to small. Min size is $min_size, but actual is $actual_size.";
        std::map<std::string, std::string> replace_map = {
                {"$field_name", options_.field_name.value_or("")},
                {"$min_size", std::to_string(size_)},
                {"$actual_size", std::to_string(actual_value)},
        };

        std::string error_message = ResultUtility::GenerateErrorMessage(
                options_.error_message_pattern.value_or(error_message_pattern), replace_map);

        auto res = Result::Builder(Result::ErrorCode::ValidateError).WithErrorMessage(error_message).Build();
        RESULT_DIRECT_RETURN(res);
    }

private:
    template <typename T>
    std::tuple<bool, size_t> validate(const T& t) {
        static_assert(has_size_v<T>, "T must have size() method");

        auto ok = t.size() >= size_;
        return std::make_tuple(ok, t.size());
    }

private:
    Options options_;
    size_t size_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_MIN_SIZE_H
