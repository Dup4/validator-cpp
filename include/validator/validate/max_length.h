#ifndef VALIDATOR_VALIDATE_MAX_LENGTH_H
#define VALIDATOR_VALIDATE_MAX_LENGTH_H

#include <cstddef>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../types_check/has_size.h"

namespace validator {

class MaxLength : OptionsBaseBuilder {
public:
    struct Options : public OptionsBase {};

public:
    MaxLength() = delete;
    template <typename... Opt>
    MaxLength(size_t len, Opt&&... opts) : len_(len) {
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
            return t.size() <= len_;
        } else {
            return true;
        }
    }

private:
    Options options_;
    size_t len_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_MAX_LENGTH_H
