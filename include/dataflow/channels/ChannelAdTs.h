#pragma once

#include "ChannelAlwaysDataAvailable.h"
#include "decorators/ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelAdTs = decorators::ChannelThreadSafetyDecorator<ChannelAlwaysDataAvailable<T>>;

} // namespace dataflow::channels
