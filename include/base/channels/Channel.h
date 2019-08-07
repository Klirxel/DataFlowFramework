#pragma once

#include <queue>

#include "ChannelBase.h"

namespace df::base {

template <typename ValueType>
class ChannelDataContainer : public ChannelDataContainerIf<ValueType> {

public:
    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    std::queue<ValueType> data_;
};

template <typename ValueType,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerAll,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = IgnoreNothing<ValueType>>
using Channel = ChannelBase<ChannelDataContainer<ValueType>, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>;

} // namespace df

#include "Channel.hpp"
