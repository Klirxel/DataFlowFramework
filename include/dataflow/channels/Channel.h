/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "ChannelBase.h"
#include "dataContainers/ChannelUnlimitedDataContainer.h"

namespace dataflow::channels {

template <typename ValueType,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerNone,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = ignorePredicates::IgnoreNothing>
using Channel = ChannelBase<dataContainers::ChannelUnlimitedDataContainer<ValueType>,
    triggerPolicyPop,
    triggerPolicyPush,
    IgnorePredicate>;

} // namespace dataflow::channels
