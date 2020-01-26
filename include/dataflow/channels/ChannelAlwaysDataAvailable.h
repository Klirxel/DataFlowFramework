/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "Channel.h"
#include "decorators/ChannelAlwaysDataAvailableDecorator.h"

namespace dataflow::channels {

template <typename T>
using ChannelAlwaysDataAvailable = decorators::ChannelAlwaysDataAvailableDecorator<Channel<T>>;

} // namespace dataflow::channels
