#pragma once

#include "Channel.h"
#include "ChannelAlwaysDataAvailableDecorator.h"
#include "ChannelCircleBuf.h"
#include "ChannelThreadSafetyDecorator.h"

namespace df::base {

template <typename T>
using ChannelThreadSafe = ChannelThreadSafetyDecorator<Channel<T>>;

template <typename T>
using ChannelAlwaysDataAvailable = ChannelAlwaysDataAvailableDecorator<Channel<T>>;

template <typename T>
using ChannelAdTs = ChannelThreadSafetyDecorator<ChannelAlwaysDataAvailable<T>>;

template <typename T, std::size_t Size>
using ChannelCircleBufThreadSafe = ChannelThreadSafetyDecorator<ChannelCircleBuf<T, Size>>;

} // namespace df
