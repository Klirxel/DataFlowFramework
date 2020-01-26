/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "../dataContainers/ChannelUnlimitedDataContainer.h"

namespace dataflow::channels::dataContainers {

template <typename T>
std::optional<T> ChannelUnlimitedDataContainer<T>::pop()
{
    std::optional<T> data;

    if (not data_.empty()) {
        data = std::move(data_.front());
        data_.pop();
    }

    return data;
}

template <typename T>
void ChannelUnlimitedDataContainer<T>::push(T&& data)
{
    data_.push(std::forward<T>(data));
}

template <typename T>
std::size_t ChannelUnlimitedDataContainer<T>::size() const
{
    return data_.size();
}

template <typename T>
std::size_t ChannelUnlimitedDataContainer<T>::max_size() const
{
    return std::numeric_limits<size_t>::max();
}

} // namespace dataflow::channels:dataContainers
