#pragma once

#include "Channel.h"
#include "decorators/ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelThreadSafeNoTrigger = decorators::ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

} // namespace dataflow::channels
