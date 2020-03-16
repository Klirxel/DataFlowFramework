/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <algorithm>

#include "../ChannelBase.h"

namespace dataflow::channels {

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
constexpr void ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::attachSinkBlock(BlockIf* sinkBlock) noexcept
{
    sinkBlockList_.push_back(sinkBlock);
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
constexpr void ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::attachSourceBlock(BlockIf* sourceBlock) noexcept
{
    sourceBlockList_.push_back(sourceBlock);
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
std::optional<typename ChannelDataContainer::ValueType> ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::pop()
{
    std::optional<ValueType> value = dataContainer_.pop();

    constexpr bool triggerSourceBlock = triggerPolicyPop == TriggerPolicy::triggerSource || triggerPolicyPop == TriggerPolicy::triggerAll;

    if (triggerSourceBlock && value) {
        notify(sourceBlockList_);
    }

    constexpr bool triggerSinkBlock = triggerPolicyPop == TriggerPolicy::triggerSink || triggerPolicyPop == TriggerPolicy::triggerAll;

    if (triggerSinkBlock && size() > 0) {
        notify(sinkBlockList_);
    }

    return value;
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
void ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::push(ValueType&& data)
{
    if (IgnorePredicate {}(data)) {
        return;
    }

    dataContainer_.push(std::forward<ValueType>(data));

    //Usage unclear yet.
    constexpr bool triggerSourceBlock = triggerPolicyPush == TriggerPolicy::triggerSource || triggerPolicyPush == TriggerPolicy::triggerAll;

    if (triggerSourceBlock && size() < max_size()) {
        notify(sourceBlockList_);
    }

    //I have still data
    constexpr bool triggerSinkBlock = triggerPolicyPush == TriggerPolicy::triggerSink || triggerPolicyPush == TriggerPolicy::triggerAll;

    if (triggerSinkBlock && size() > 0) {
        notify(sinkBlockList_);
    }
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
bool ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::dataAvailable() const
{
    const bool dataAvailable = dataContainer_.size() > 0;
    return dataAvailable;
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
bool ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::dataAssignable() const
{
    const bool dataAssignable = dataContainer_.size() < dataContainer_.max_size();
    return dataAssignable;
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
std::size_t ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::size() const
{
    return dataContainer_.size();
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
std::size_t ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::max_size() const
{
    return dataContainer_.max_size();
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
void ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::notify(const std::vector<BlockIf*>& blockList)
{
    auto notifyBlock = [](BlockIf* block) {
        block->execute();
    };

    //note: inform all block strategy. Perhaps there is a more elegant way.
    std::for_each(blockList.begin(), blockList.end(), notifyBlock);
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
void ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::notifySourceBlockList()
{
    constexpr bool triggerSourceBlock = triggerPolicyPop == TriggerPolicy::triggerSource || triggerPolicyPop == TriggerPolicy::triggerAll;

    if constexpr (triggerSourceBlock) {
        notify(sourceBlockList_);
    }
}

template <class ChannelDataContainer, TriggerPolicy triggerPolicyPop, TriggerPolicy triggerPolicyPush, typename IgnorePredicate>
void ChannelBase<ChannelDataContainer, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>::notifySinkBlockList()
{
    constexpr bool triggerSinkBlock = triggerPolicyPop == TriggerPolicy::triggerSink || triggerPolicyPop == TriggerPolicy::triggerAll;

    if constexpr (triggerSinkBlock) {
        notify(sinkBlockList_);
    }
}

} // namespace dataflow::channels
