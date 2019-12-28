#pragma once

#include "Channel.h"
#include "decorators/ChannelAlwaysDataAvailableDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelAlwaysDataAvailableNoTrigger = decorators::ChannelAlwaysDataAvailableDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

} // namespace dataflow::channels
