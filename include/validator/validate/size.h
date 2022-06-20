#ifndef VALIDATOR_VALIDATE_SIZE_H
#define VALIDATOR_VALIDATE_SIZE_H

#include <cstddef>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/validator.h"
#include "../types_check/has_size.h"

namespace validator {

class Size : public OptionsBaseBuilder {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    Size() = delete;
    template <typename... Opt>
    Size(size_t min_size, size_t max_size, Opt&&... opts) : min_size_(min_size), max_size_(max_size) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto [ok, actual_value] = validate(t);

        if (ok) {
            return ValidResult;
        }

        std::string error_message_pattern =
                "The size of `$field_name` is not valid. The range of sizes is [$min_size, $max_size], but actual is $actual_size.";
        std::map<std::string, std::string> replace_map = {
                {"$field_name", options_.field_name.value_or("")},
                {"$min_size", std::to_string(min_size_)},
                {"$max_size", std::to_string(max_size_)},
                {"$actual_size", std::to_string(actual_value)},
        };

        std::string error_message =
                GenerateErrorMessage(options_.error_message_pattern.value_or(error_message_pattern), replace_map);

        return ResultBuilder().WithIsValidation(false).WithErrorMessage(error_message).Build();
    }

private:
    template <typename T>
    std::tuple<bool, size_t> validate(const T& t) {
        static_assert(has_size_v<T>, "T must have size() method");

        auto ok = t.size() >= min_size_ && t.size() <= max_size_;
        return std::make_tuple(ok, t.size());
    }

private:
    Options options_;
    size_t min_size_;
    size_t max_size_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_SIZE_H
