/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

namespace dataflow::channels::ignorePredicates {

/**
 * @brief Accept every value 
 */
struct IgnoreNothing {

    template <typename ValueType>
    [[nodiscard]] constexpr bool operator()([[maybe_unused]] const ValueType& val) const noexcept;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreNothing.hpp"
