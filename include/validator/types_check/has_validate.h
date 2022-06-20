#ifndef VALIDATOR_TYPES_CHECK_HAS_VALIDATE_H
#define VALIDATOR_TYPES_CHECK_HAS_VALIDATE_H

#include <type_traits>
#include <vector>

namespace validator {

template <typename T>
class has_validate {
private:
    template <typename U>
    static constexpr auto check(int) -> decltype(std::declval<U>().Validate(), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_validate_v = has_validate<T>::value;

}  // namespace validator

#endif  // VALIDATOR_TYPES_CHECK_HAS_VALIDATE_H
