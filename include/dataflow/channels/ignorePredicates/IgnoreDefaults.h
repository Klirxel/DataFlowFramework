/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "../../tools/is_compareable.h"

namespace dataflow::channels::ignorePredicates {

/**
 * @brief Ignore default constructed values.
 */
struct IgnoreDefaults {

    template <typename ValueType,
        typename = std::enable_if_t<std::is_default_constructible_v<ValueType>>,
        typename = std::enable_if_t<tools::is_compareable_v<ValueType, ValueType>>>
    [[nodiscard]] bool operator()([[maybe_unused]] const ValueType& val) const;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreDefaults.hpp"
