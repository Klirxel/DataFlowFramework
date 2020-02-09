/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "../ChannelIf.h"

namespace dataflow::channels {

template <typename T>
[[nodiscard]] constexpr std::mutex& ChannelIf<T>::getLock() noexcept
{
    return lock;
}

} // namespace dataflow::channels
