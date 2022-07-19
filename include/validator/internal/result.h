#ifndef VALIDATOR_INTERNAL_RESULT_H
#define VALIDATOR_INTERNAL_RESULT_H

#include <map>
#include <string>

namespace validator {

struct Result {
    bool IsValidation{false};
    std::string ErrorMessage{""};
};

class ResultBuilder {
public:
    ResultBuilder& WithIsValidation(bool IsValidation = true) {
        result.IsValidation = IsValidation;
        return *this;
    }

    ResultBuilder& WithErrorMessage(const std::string& ErrorMessage) {
        result.ErrorMessage = ErrorMessage;
        return *this;
    }

    Result Build() {
        return result;
    }

private:
    Result result;
};

inline const static auto ValidResult = ResultBuilder().WithIsValidation(true).Build();

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_RESULT_H
