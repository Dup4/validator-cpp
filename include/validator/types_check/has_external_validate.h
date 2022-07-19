#ifndef VALIDATOR_TYPES_CHECK_HAS_EXTERNAL_VALIDATE_H
#define VALIDATOR_TYPES_CHECK_HAS_EXTERNAL_VALIDATE_H

#include <type_traits>

namespace validator {

template <typename T>
class has_external_validate {
private:
    template <typename U>
    static constexpr auto check(int) -> decltype(__ValidatorExternal_Validate(std::declval<U>()), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_external_validate_v = has_external_validate<T>::value;

}  // namespace validator

#endif  // VALIDATOR_TYPES_CHECK_HAS_EXTERNAL_VALIDATE_H
