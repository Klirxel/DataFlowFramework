/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "../ignorePredicates/IgnoreDefaults.h"

namespace dataflow::channels::ignorePredicates {

template <typename ValueType, typename, typename>
[[nodiscard]] bool IgnoreDefaults::operator()(const ValueType& val) const
{
    return val == ValueType {};
}

} // namespace dataflow::channels::ignorePredicates
