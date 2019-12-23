#pragma once

#include "ChannelBase.h"
#include "dataContainers/ChannelDataContainer.h"

namespace dataflow::channels {

template <typename ValueType,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerNone,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = ignorePredicates::IgnoreNothing>
using Channel = ChannelBase<dataContainers::ChannelDataContainer<ValueType>,
    triggerPolicyPop,
    triggerPolicyPush,
    IgnorePredicate>;

} // namespace dataflow::channels
