#pragma once

#include "Channel.h"
#include "ChannelAlwaysDataAvailableDecorator.h"
#include "ChannelCircleBuf.h"
#include "ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelThreadSafe = ChannelThreadSafetyDecorator<Channel<T>>;

template <typename T>
using ChannelThreadSafeNoTrigger = ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

template <typename T>
using ChannelThreadSafeIgnoreDefaults = ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerAll, TriggerPolicy::triggerSink, IgnoreDefaults<T>>>;

template <typename T>
using ChannelAlwaysDataAvailable = ChannelAlwaysDataAvailableDecorator<Channel<T>>;

template <typename T>
using ChannelAlwaysDataAvailableNoTrigger = ChannelAlwaysDataAvailableDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

template <typename T>
using ChannelAdTs = ChannelThreadSafetyDecorator<ChannelAlwaysDataAvailable<T>>;

template <typename T, std::size_t Size>
using ChannelCircleBufThreadSafe = ChannelThreadSafetyDecorator<ChannelCircleBuf<T, Size>>;

} // namespace df
