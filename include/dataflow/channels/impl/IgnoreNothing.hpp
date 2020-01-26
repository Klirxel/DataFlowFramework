/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "../ignorePredicates/IgnoreNothing.h"

namespace dataflow::channels::ignorePredicates {

template <typename ValueType>
[[nodiscard]] constexpr bool IgnoreNothing::operator()([[maybe_unused]] const ValueType& val) const noexcept
{
    return false;
}

} // namespace dataflow::channels::ignorePredicates
