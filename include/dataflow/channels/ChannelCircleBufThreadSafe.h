#pragma once

#include "Channel.h"
#include "ChannelCircleBuf.h"
#include "decorators/ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <typename T, std::size_t Size>
using ChannelCircleBufThreadSafe = decorators::ChannelThreadSafetyDecorator<ChannelCircleBuf<T, Size>>;

} // namespace dataflow::channels
