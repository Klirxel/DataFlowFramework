/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

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
