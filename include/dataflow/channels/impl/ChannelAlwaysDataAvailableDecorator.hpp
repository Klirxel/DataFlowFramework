/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <limits>

#include "../decorators/ChannelAlwaysDataAvailableDecorator.h"

namespace dataflow::channels::decorators {

template <class CHANNEL>
void ChannelAlwaysDataAvailableDecorator<CHANNEL>::attachSinkBlock(BlockIf* block)
{
    chan_.attachSinkBlock(block);
}

template <class CHANNEL>
void ChannelAlwaysDataAvailableDecorator<CHANNEL>::attachSourceBlock(BlockIf* block)
{
    chan_.attachSourceBlock(block);
}

template <class CHANNEL>
std::optional<typename CHANNEL::ValueType> ChannelAlwaysDataAvailableDecorator<CHANNEL>::pop()
{
    return chan_.dataAvailable() ? chan_.pop() : std::optional<ValueType> { ValueType {} };
}

template <class CHANNEL>
void ChannelAlwaysDataAvailableDecorator<CHANNEL>::push(typename CHANNEL::ValueType&& data)
{
    return chan_.push(std::forward<ValueType>(data));
}

template <class CHANNEL>
bool ChannelAlwaysDataAvailableDecorator<CHANNEL>::dataAvailable() const
{
    return true;
}

template <class CHANNEL>
bool ChannelAlwaysDataAvailableDecorator<CHANNEL>::dataAssignable() const
{
    return chan_.dataAssignable();
}

template <class CHANNEL>
[[nodiscard]] constexpr size_t ChannelAlwaysDataAvailableDecorator<CHANNEL>::size() const
{
    return std::numeric_limits<size_t>::max();
}

template <class CHANNEL>
[[nodiscard]] constexpr size_t ChannelAlwaysDataAvailableDecorator<CHANNEL>::max_size() const
{
    return std::numeric_limits<size_t>::max();
}

} // namespace dataflow::channels::decorators 
