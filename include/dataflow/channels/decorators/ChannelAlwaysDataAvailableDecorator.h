/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <type_traits>

#include "../../blocks/BlockIf.h"
#include "../ChannelIf.h"

namespace dataflow::channels::decorators {

using namespace dataflow::blocks;

/**
 * @brief ChannelDecorator 
 *
 * @details
 * - can be used to decorate a channel to have
 *   always data available.
 * - this means that pop() always returns an 
 *   value and dataAvailable() is always true.
 * - if no value is available, a value is 
 *   default contructed.
 * - normally used when a block has multiple 
 *   block inputs and the channel should not
 *   block triggering the channel when no data
 *   is available.
 * - Requires the ValueType to be default constructible.
 */
template <class CHANNEL>
class ChannelAlwaysDataAvailableDecorator : public ChannelIf<typename CHANNEL::ValueType> {

public:
    using ValueType = typename CHANNEL::ValueType;

    static_assert(std::is_base_of_v<ChannelIf<ValueType>, CHANNEL>, "CHANNEL is not derived from ChannelIf<T>");
    static_assert(std::is_default_constructible_v<CHANNEL>, "CHANNEL is not default constructible.");
    static_assert(std::is_default_constructible_v<ValueType>, "ValueType is not default constructible.");

    void attachSinkBlock(BlockIf* /*block*/) override;
    void attachSourceBlock(BlockIf* /*block*/) override;

    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] constexpr std::size_t size() const override;
    [[nodiscard]] constexpr std::size_t max_size() const override;

private:
    CHANNEL chan_;
};

} // namespace dataflow::channels::decorators

#include "../impl/ChannelAlwaysDataAvailableDecorator.hpp"
