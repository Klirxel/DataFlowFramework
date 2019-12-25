#pragma once

#include "Channel.h"
#include "ChannelCircleBuf.h"
#include "decorators/ChannelAlwaysDataAvailableDecorator.h"
#include "decorators/ChannelThreadSafetyDecorator.h"
#include "ignorePredicates/IgnoreDefaults.h"

#include "ChannelAlwaysDataAvailable.h"
#include "ChannelThreadSafeIgnoreDefaults.h"
#include "ChannelThreadSafeNoTrigger.h"
#include "ChannelThreadSave.h"

namespace dataflow::channels {

template <typename T>
using ChannelAlwaysDataAvailableNoTrigger = decorators::ChannelAlwaysDataAvailableDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

template <typename T>
using ChannelAdTs = decorators::ChannelThreadSafetyDecorator<ChannelAlwaysDataAvailable<T>>;

template <typename T, std::size_t Size>
using ChannelCircleBufThreadSafe = decorators::ChannelThreadSafetyDecorator<ChannelCircleBuf<T, Size>>;

} // namespace dataflow::channels
