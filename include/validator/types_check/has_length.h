#ifndef VALIDATOR_TYPES_CHECK_HAS_LENGTH_H
#define VALIDATOR_TYPES_CHECK_HAS_LENGTH_H

#include <type_traits>
#include <vector>

namespace validator {

template <typename T>
class has_length {
private:
    template <typename U>
    static constexpr auto check(int) -> decltype(std::declval<U>().length(), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_length_v = has_length<T>::value;

}  // namespace validator

#endif  // VALIDATOR_TYPES_CHECK_HAS_LENGTH_H
