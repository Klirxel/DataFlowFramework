/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "Channel.h"
#include "decorators/ChannelThreadSafetyDecorator.h"
#include "ignorePredicates/IgnoreDefaults.h"

namespace dataflow::channels {

template <typename T>
using ChannelThreadSafeIgnoreDefaults = decorators::ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerAll, TriggerPolicy::triggerSink, ignorePredicates::IgnoreDefaults>>;

} // namespace dataflow::channels
