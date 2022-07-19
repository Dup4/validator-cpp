#ifndef VALIDATOR_TYPES_CHECK_HAS_INTERNAL_VALIDATE_H
#define VALIDATOR_TYPES_CHECK_HAS_INTERNAL_VALIDATE_H

#include <type_traits>

namespace validator {

template <typename T>
class has_internal_validate {
private:
    template <typename U>
    static constexpr auto check(int) -> decltype(std::declval<U>().__Validator_Validate(), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_internal_validate_v = has_internal_validate<T>::value;

}  // namespace validator

#endif  // VALIDATOR_TYPES_CHECK_HAS_INTERNAL_VALIDATE_H
