#ifndef VALIDATOR_VALIDATE_LENGTH_H
#define VALIDATOR_VALIDATE_LENGTH_H

#include <cstddef>

#include "../internal/options.h"
#include "../internal/result.h"
#include "../types_check/has_size.h"

namespace validator {

class Length : OptionsBaseBuilder {
public:
    struct Options : public OptionsBase {};

public:
    Length() = delete;
    template <typename... Opt>
    Length(size_t min_len, size_t max_len, Opt&&... opts) : min_len_(min_len), max_len_(max_len) {
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
            return t.size() >= min_len_ && t.size() <= max_len_;
        } else {
            return true;
        }
    }

private:
    Options options_;
    size_t min_len_;
    size_t max_len_;
};

}  // namespace validator

#endif  // VALIDATOR_VALIDATE_LENGTH_H
