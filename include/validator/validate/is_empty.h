#ifndef VALIDATOR_VALIDATE_IS_EMPTY_H
#define VALIDATOR_VALIDATE_IS_EMPTY_H

#include <cstddef>
#include <utility>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../internal/result_utility.h"
#include "../internal/validator.h"
#include "../types_check/has_empty.h"

namespace validator {

class IsEmpty : public OptionsBaseBuilder {
    friend class ::validator::Validator;

public:
    struct Options : public OptionsBase {};

public:
    template <typename... Opt>
    IsEmpty(Opt&&... opts) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto ok = validate(t);
        if (ok) {
            return Result::OK();
        }

        std::string error_message_pattern = "`$field_name` is not empty.";
        std::map<std::string, std::string> replace_map = {
                {"$field_name", options_.field_name.value_or("")},
        };

        std::string error_message = ResultUtility::GenerateErrorMessage(
                options_.error_message_pattern.value_or(error_message_pattern), replace_map);

        auto res = Result::Builder(Result::ErrorCode::ValidateError).WithErrorMessage(error_message).Build();
        RESULT_DIRECT_RETURN(res);
    }

private:
    template <typename T>
    bool validate(const T& t) {
        static_assert(has_empty_v<T>, "T must have empty() method");

        auto ok = t.empty();
        return ok;
    }

private:
    Options options_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_IS_EMPTY_H
