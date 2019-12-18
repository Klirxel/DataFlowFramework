#pragma once

#include "ChannelBase.h"
#include "dataContainers/ChannelCircleBufContainer.h"

namespace dataflow::channels {

template <typename ValueType, std::size_t Size>
using ChannelCircleBuf = ChannelBase<dataContainers::ChannelCircleBufContainer<ValueType, Size>>;

} // namespace dataflow::channels
