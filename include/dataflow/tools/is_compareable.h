#pragma once

#include "impl/is_compareable_impl.hpp"

namespace dataflow::tools {

template <typename T, typename U>
struct is_compareable : impl::is_compareable_impl<T, U> {
};

template <typename T, typename U>
static constexpr bool is_compareable_v = is_compareable<T, U>::value;

} // namespace dataflow::tools