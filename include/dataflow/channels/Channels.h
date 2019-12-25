#pragma once

#include "Channel.h"
#include "ChannelCircleBuf.h"
#include "decorators/ChannelAlwaysDataAvailableDecorator.h"
#include "decorators/ChannelThreadSafetyDecorator.h"
#include "ignorePredicates/IgnoreDefaults.h"

#include "ChannelAlwaysDataAvailable.h"
#include "ChannelCircleBufThreadSafe.h"
#include "ChannelDataAvailableNoTrigger.h"
#include "ChannelThreadSafeIgnoreDefaults.h"
#include "ChannelThreadSafeNoTrigger.h"
#include "ChannelThreadSave.h"

namespace dataflow::channels {

template <typename T>
using ChannelAdTs = decorators::ChannelThreadSafetyDecorator<ChannelAlwaysDataAvailable<T>>;

} // namespace dataflow::channels
