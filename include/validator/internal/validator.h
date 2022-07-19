#ifndef VALIDATOR_INTERNAL_VALIDATOR_H
#define VALIDATOR_INTERNAL_VALIDATOR_H

#include "./inject_entrance.h"
#include "./result.h"

namespace validator {

class Validator {
public:
    template <typename T, typename V>
    static void ExecuteValidate(const T& t, const std::string& field_name, V&& v, Result& res) {
        if (!res.IsOK()) {
            return;
        }

        if (!v.options_.field_name.has_value()) {
            v.options_.field_name = field_name;
        }

        res = v.Validate(t);
    }

    template <typename T, typename... V>
    static Result ExecuteMultiValidate(const T& t, const std::string& field_name, V&&... v) {
        auto res = Result::OK();

        (ExecuteValidate(t, field_name, std::forward<V>(v), res), ...);

        RESULT_DIRECT_RETURN(res);
    }

    template <typename T>
    static Result Validate(const T& t) {
        return InjectEntrance::Validate(t);
    }
};

}  // namespace validator

using Validator = ::validator::Validator;

#endif  // VALIDATOR_INTERNAL_VALIDATOR_H
