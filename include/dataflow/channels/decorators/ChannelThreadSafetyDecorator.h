/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <mutex>
#include <type_traits>

#include "../../blocks/BlockIf.h"
#include "../ChannelIf.h"

namespace dataflow::channels::decorators {

using dataflow::blocks::BlockIf;

/**
 * @brief ChannelDecorator 
 *
 * @details
 * - can be used to decorate a channel to be 
 *   thread save.
 * - internally delays the operation of member function
 *   until it is not used in another thread context.
 */
template <class CHANNEL>
class ChannelThreadSafetyDecorator : public ChannelIf<typename CHANNEL::ValueType> {

    using ValueType = typename CHANNEL::ValueType;

    static_assert(std::is_base_of_v<ChannelIf<ValueType>, CHANNEL>, "CHANNEL is not derived from ChannelIf<T>");
    static_assert(std::is_default_constructible_v<CHANNEL>, "CHANNEL is not default constructible.");

public:
    void attachSinkBlock(BlockIf* /*block*/) override;
    void attachSourceBlock(BlockIf* /*block*/) override;

    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    mutable std::mutex mutex_;
    CHANNEL chan_;
};

} // namespace dataflow::channels::decorators

#include "../impl/ChannelThreadSafetyDecorator.hpp"
