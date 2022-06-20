#ifndef VALIDATOR_INTERNAL_OPTIONS_H
#define VALIDATOR_INTERNAL_OPTIONS_H

#include <optional>
#include <string>

namespace validator {

struct OptionsBase {
    std::optional<std::string> field_name{std::nullopt};
    std::optional<std::string> error_message{std::nullopt};
};

class OptionsBaseBuilder {
public:
    static auto WithFieldName(const std::string& field_name) {
        return [field_name](auto& t) {
            t.field_name = field_name;
        };
    }

    static auto WithErrorMessage(const std::string& error_message) {
        return [error_message](auto& t) {
            t.error_message = error_message;
        };
    }
};

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_OPTIONS_H
