#ifndef VALIDATOR_INTERNAL_RESULT_H
#define VALIDATOR_INTERNAL_RESULT_H

#include <string>

namespace validator {

struct Result {
    bool isValidation{false};
    std::string errorMessage{""};
};

class ResultBuilder {
public:
    ResultBuilder& WithIsValidation(bool isValidation) {
        result.isValidation = isValidation;
        return *this;
    }

    ResultBuilder& WithErrorMessage(const std::string& errorMessage) {
        result.errorMessage = errorMessage;
        return *this;
    }

    Result Build() {
        return result;
    }

private:
    Result result;
};

}  // namespace validator

#endif  // VALIDATOR_INTERNAL_RESULT_H
