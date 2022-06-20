#ifndef VALIDATOR_INTERNAL_MACROS_H
#define VALIDATOR_INTERNAL_MACROS_H

#include "./result.h"

namespace validator {

template <typename T, typename V>
void ExecuteValidate(const T& t, [[maybe_unused]] const std::string& field_name, V&& v, Result& res) {
    if (!res.isValidation) {
        return;
    }

    res = v.Validate(t);
}

template <typename T, typename... V>
Result ExecuteMultiValidate(const T& t, const std::string& field_name, V&&... v) {
    auto res = ResultBuilder().WithIsValidation(true).Build();

    (ExecuteValidate(t, field_name, std::forward<V>(v), res), ...);

    return res;
}

#define VALIDATOR_BEGIN \
                        \
public:                 \
    Result Validate() {
#define VALIDATOR_END                                                 \
    return validator::ResultBuilder().WithIsValidation(true).Build(); \
    }

#define VALIDATOR_DECLARE(field, ...)                                  \
    {                                                                  \
        auto res = ExecuteMultiValidate(field, #field, ##__VA_ARGS__); \
        if (!res.isValidation) {                                       \
            return res;                                                \
        }                                                              \
    }

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_MACROS_H
