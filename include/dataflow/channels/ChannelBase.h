/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <optional>
#include <type_traits>
#include <vector>

#include "../blocks/BlockIf.h"
#include "../channels/ChannelIf.h"
#include "TriggerPolicy.h"
#include "dataContainers/ChannelDataContainerIf.h"
#include "ignorePredicates/IgnoreNothing.h"

namespace dataflow::channels {

using dataflow::blocks::BlockIf;
using dataflow::channels::ChannelIf;
using dataflow::channels::dataContainers::ChannelDataContainerIf;

/**
 * @brief Basic channel implementation
 *
 * @tparam ChannelDataContainer Buffer type used to store channel data input.
 *                              See \ref dataContainers for options.
 * @tparam triggerPolicyPop     Control if source- or sink-blocks should be triggerd
 *                              in case data is popped from the channel.
 *                              See \ref TriggerPolicy for options.
 * @tparam triggerPolicyPush    Control if source- or sink-blocks should be triggerd
 *                              in case data is pushed form the channel.
 *                              See \ref TriggerPolicy for options.
 * @tparam IgnorePredicate      Configure which type of data should be ignored when
 *                              pushed to a channel.
 *                              See \ref ignorePredicates
 *                              for options.
 */
template <class ChannelDataContainer,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerAll,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = ignorePredicates::IgnoreNothing>
class ChannelBase : public ChannelIf<typename ChannelDataContainer::ValueType> {

    static_assert(std::is_base_of_v<
                      ChannelDataContainerIf<typename ChannelDataContainer::ValueType>,
                      ChannelDataContainer>,
        "ChannelDataContainer has to be derived form ChannelDataContainerIf");

    static_assert(std::is_invocable_r_v<bool, IgnorePredicate,
                      typename ChannelDataContainer::ValueType&>,
        "Ignore predicate is not valid.");

public:
    using ValueType = typename ChannelDataContainer::ValueType;

    constexpr void attachSinkBlock(BlockIf* block) noexcept override;
    constexpr void attachSourceBlock(BlockIf* block) noexcept override;
    std::optional<ValueType> pop() override;
    void push(ValueType&& data) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    void notify(const std::vector<BlockIf*>& blockList);
    void notifySourceBlockList();
    void notifySinkBlockList();

    std::vector<BlockIf*> sinkBlockList_;
    std::vector<BlockIf*> sourceBlockList_;
    ChannelDataContainer dataContainer_;
};

} // namespace dataflow::channels

#include "impl/ChannelBase.hpp"
