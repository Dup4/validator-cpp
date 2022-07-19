#ifndef VALIDATOR_INTERNAL_RESULT_UTILITY_H
#define VALIDATOR_INTERNAL_RESULT_UTILITY_H

#include <map>
#include <string>

namespace validator {

class ResultUtility {
public:
    static std::string GenerateErrorMessage(const std::string& error_message_pattern,
                                            const std::map<std::string, std::string> replace_map = {}) {
        if (error_message_pattern.empty()) {
            return error_message_pattern;
        }

        std::string res = "";

        size_t len = error_message_pattern.length();
        for (size_t i = 0; i < len; i++) {
            bool replace = false;
            for (const auto& [k, v] : replace_map) {
                if (i + k.length() <= len && error_message_pattern.substr(i, k.length()) == k) {
                    res += v;
                    i += k.length() - 1;
                    replace = true;
                    break;
                }
            }

            if (!replace) {
                res += error_message_pattern[i];
            }
        }

        return res;
    }
};

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_RESULT_UTILITY_H
