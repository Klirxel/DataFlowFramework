/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "impl/is_compareable_impl.hpp"

namespace dataflow::tools {

/**
 * @brief type trait: checks if types are compareable 
 */
template <typename T, typename U>
struct is_compareable : impl::is_compareable_impl<T, U> {
};

/**
 * @brief helper variable template
 */
template <typename T, typename U>
static constexpr bool is_compareable_v = is_compareable<T, U>::value;

} // namespace dataflow::tools
