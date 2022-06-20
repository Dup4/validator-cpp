#ifndef VALIDATOR_INTERNAL_OPTIONS_H
#define VALIDATOR_INTERNAL_OPTIONS_H

#include <optional>
#include <string>

namespace validator {

struct OptionsBase {
    std::optional<std::string> field_name{std::nullopt};
    std::optional<std::string> error_message_pattern{std::nullopt};
};

class OptionsBaseBuilder {
public:
    static auto WithFieldName(const std::string& field_name) {
        return [field_name](auto& t) {
            t.field_name = field_name;
        };
    }

    static auto WithErrorMessagePattern(const std::string& error_message_pattern) {
        return [error_message_pattern](auto& t) {
            t.error_message_pattern = error_message_pattern;
        };
    }
};

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_OPTIONS_H
