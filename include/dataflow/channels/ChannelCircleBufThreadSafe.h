/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "Channel.h"
#include "ChannelCircleBuf.h"
#include "decorators/ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <typename T, std::size_t Size>
using ChannelCircleBufThreadSafe = decorators::ChannelThreadSafetyDecorator<ChannelCircleBuf<T, Size>>;

} // namespace dataflow::channels
