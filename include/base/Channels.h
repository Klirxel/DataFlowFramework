#pragma once

#include "Channel.h"
#include "ChannelThreadSafetyDecorator.h"

namespace df::base {

template <typename T>
using ChannelThreadSafe = ChannelThreadSafetyDecorator<T, Channel>;

} // namespace df
