#ifndef VALIDATOR_TYPES_CHECK_IS_VECTOR_H
#define VALIDATOR_TYPES_CHECK_IS_VECTOR_H

#include <type_traits>
#include <vector>

namespace validator {

template <typename T>
struct is_vector : std::false_type {};

template <typename T>
struct is_vector<std::vector<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;

}  // namespace validator

#endif  // VALIDATOR_TYPES_CHECK_IS_VECTOR_H
