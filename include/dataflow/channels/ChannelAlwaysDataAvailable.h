#pragma once

#include "Channel.h"
#include "decorators/ChannelAlwaysDataAvailableDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelAlwaysDataAvailable = decorators::ChannelAlwaysDataAvailableDecorator<Channel<T>>;

} // namespace dataflow::channels
