#pragma once

#include <type_traits>

namespace dataflow::tools::impl {

template <typename T, typename U, typename = bool>
struct is_compareable_impl : std::false_type {
};

template <typename T, typename U>
struct is_compareable_impl<T, U, decltype(std::declval<T>() == std::declval<U>())>
    : std::true_type {
};

} // namespace dataflow::tools::impl
