#pragma once

#include <queue>

#include "ChannelBase.h"

namespace dataflow::channels {

template <typename ValueType>
class ChannelDataContainer : public dataContainers::ChannelDataContainerIf<ValueType> {

public:
    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    std::queue<ValueType> data_;
};

template <typename ValueType,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerNone,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = ignorePredicates::IgnoreNothing>
using Channel = ChannelBase<ChannelDataContainer<ValueType>, triggerPolicyPop, triggerPolicyPush, IgnorePredicate>;

} // namespace df

#include "impl/Channel.hpp"
