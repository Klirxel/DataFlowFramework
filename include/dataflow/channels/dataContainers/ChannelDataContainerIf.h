/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <optional>
#include <type_traits>

namespace dataflow::channels::dataContainers {

/**
 * @brief Generic interface for channel data containers.
 *
 * @details
 * - Generic interface for data containers set can be
 *   assigned to a \ref ChannelBase.
 */
template <typename ValueType_>
struct ChannelDataContainerIf {

    static_assert(std::is_move_constructible_v<ValueType_>, "Value type has to be move constructible.");
    static_assert(std::is_move_assignable_v<ValueType_>, "Value type has to be move assignable.");

    using ValueType = ValueType_;

    virtual std::optional<ValueType> pop() = 0;
    virtual void push(ValueType&& data) = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual std::size_t max_size() const = 0;
};

} // namespace dataflow::channels::dataContainers
