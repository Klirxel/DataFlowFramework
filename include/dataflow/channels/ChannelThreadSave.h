#pragma once

#include "Channel.h"
#include "decorators/ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelThreadSafe = decorators::ChannelThreadSafetyDecorator<Channel<T>>;

} // namespace dataflow::channels
