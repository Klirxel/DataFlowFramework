#pragma once

#include "Channel.h"
#include "ChannelThreadSafetyDecorator.h"
#include "ChannelAlwaysDataAvailableDecorator.h"

namespace df::base {

template <typename T>
using ChannelThreadSafe = ChannelThreadSafetyDecorator<T, Channel>;

template <typename T>
using ChannelAlwaysDataAvailable = ChannelAlwaysDataAvailableDecorator<T, Channel>;

template <typename T>
using ChannelAdTs = ChannelThreadSafetyDecorator<T, ChannelAlwaysDataAvailable>;

} // namespace df
