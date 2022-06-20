#ifndef VALIDATOR_MIN_LENGTH_H
#define VALIDATOR_MIN_LENGTH_H

#include <cstddef>

#include "validator/options.h"
#include "validator/result.h"
#include "validator/types_check/has_size.h"

namespace validator {

class MinLength : OptionsBaseBuilder {
public:
    struct Options : public OptionsBase {};

public:
    MinLength() = delete;
    template <typename... Opt>
    MinLength(size_t len, Opt&&... opts) : len_(len) {
        (std::forward<Opt>(opts)(options_), ...);
    }

    template <typename T>
    Result Validate(const T& t) {
        auto ok = validate(t);
        return ResultBuilder().WithIsValidation(ok).Build();
    }

private:
    template <typename T>
    bool validate(const T& t) {
        if constexpr (has_size_v<T>) {
            return t.size() >= len_;
        } else {
            return true;
        }
    }

private:
    Options options_;
    size_t len_;
};

}  // namespace validator

#endif  // VALIDATOR_MIN_LENGTH_H
