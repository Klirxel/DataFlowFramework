#pragma once

#include "Channel.h"
#include "decorators/ChannelThreadSafetyDecorator.h"
#include "ignorePredicates/IgnoreDefaults.h"

namespace dataflow::channels {

template <typename T>
using ChannelThreadSafeIgnoreDefaults = decorators::ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerAll, TriggerPolicy::triggerSink, ignorePredicates::IgnoreDefaults>>;

} // namespace dataflow::channels
