#ifndef VALIDATOR_INTERNAL_VALIDATOR_H
#define VALIDATOR_INTERNAL_VALIDATOR_H

#include "./result.h"

namespace validator {

class Validator {
public:
    template <typename T, typename V>
    static void ExecuteValidate(const T& t, [[maybe_unused]] const std::string& field_name, V&& v, Result& res) {
        if (!res.isValidation) {
            return;
        }

        if (!v.options_.field_name.has_value()) {
            v.options_.field_name = field_name;
        }

        res = v.Validate(t);
    }

    template <typename T, typename... V>
    static Result ExecuteMultiValidate(const T& t, const std::string& field_name, V&&... v) {
        auto res = ResultBuilder().WithIsValidation(true).Build();

        (ExecuteValidate(t, field_name, std::forward<V>(v), res), ...);

        return res;
    }
};

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_VALIDATOR_H
