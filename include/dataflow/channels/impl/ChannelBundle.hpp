/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <algorithm>
#include <utility>

#include "../ChannelBundle.h"

namespace dataflow::channels {

template <typename... T>
constexpr ChannelBundle<T...>::ChannelBundle(
    ChannelIf<T>&... channels) noexcept
    : channels_(channels...)
{
}

template <typename... T>
constexpr void ChannelBundle<T...>::attachSinkBlock(BlockIf* block) noexcept
{
    attachSinkBlockImpl(block, std::index_sequence_for<T...>());
}

template <typename... T>
constexpr void ChannelBundle<T...>::attachSourceBlock(BlockIf* block) noexcept
{
    attachSourceBlockImpl(block, std::index_sequence_for<T...>());
}

template <typename... T>
template <size_t... Is>
constexpr void ChannelBundle<T...>::attachSinkBlockImpl(BlockIf* block, std::index_sequence<Is...> /*unused*/) noexcept
{
    (at<Is>().attachSinkBlock(block), ...);
}

template <typename... T>
template <size_t... Is>
constexpr void ChannelBundle<T...>::attachSourceBlockImpl(BlockIf* block, std::index_sequence<Is...> /*unused*/) noexcept
{
    (at<Is>().attachSourceBlock(block), ...);
}

template <typename... T>
std::optional<std::tuple<T...>> ChannelBundle<T...>::pop()
{
    return popImpl(std::index_sequence_for<T...>());
}

template <typename... T>
template <size_t... Is>
std::optional<std::tuple<T...>> ChannelBundle<T...>::popImpl(std::index_sequence<Is...> /*unused*/)
{
    std::array<std::lock_guard<std::mutex>, sizeof...(Is)>
        lockAllChannels { std::lock_guard { std::get<Is>(channels_).lock }... };

    if (dataAvailable()) {
        return std::optional<std::tuple<T...>> { std::tuple<T...> { std::move(std::get<Is>(channels_).pop()).value()... } };
    }

    return std::optional<std::tuple<T...>> {};
}

template <typename... T>
void ChannelBundle<T...>::push(std::tuple<T...>&& data, const std::array<bool, sizeof...(T)>& outputToChan)
{
    pushImpl(std::move(data), outputToChan, std::index_sequence_for<T...>());
}

template <typename... T>
[[nodiscard]] bool ChannelBundle<T...>::dataAvailable() const
{
    return dataAvailableImpl(std::index_sequence_for<T...> {});
}

template <typename... T>
[[nodiscard]] bool ChannelBundle<T...>::dataAssignable() const
{
    return dataAssignableImpl(std::index_sequence_for<T...> {});
}

template <typename... T>
[[nodiscard]] size_t ChannelBundle<T...>::size() const
{
    return sizeImpl(std::index_sequence_for<T...> {});
}

template <typename... T>
[[nodiscard]] size_t ChannelBundle<T...>::max_size() const
{
    return max_sizeImpl(std::index_sequence_for<T...> {});
}

template <typename... T>
template <size_t... Is>
void ChannelBundle<T...>::pushImpl(std::tuple<T...>&& data, const std::array<bool, sizeof...(T)>& outputToChan, std::index_sequence<Is...> /*unused*/)
{
    ((outputToChan.at(Is) && (std::get<Is>(channels_).push(std::move(std::get<Is>(data))), true)), ...);
}

template <typename... T>
template <size_t I>
constexpr typename ChannelBundle<T...>::template ChannelType<I>&
ChannelBundle<T...>::at() noexcept
{
    return std::get<I>(channels_);
}

template <typename... T>
template <size_t I>
constexpr const typename ChannelBundle<T...>::template ChannelType<I>&
ChannelBundle<T...>::at() const noexcept
{
    return std::get<I>(channels_);
}

template <typename... T>
template <size_t... Is>
[[nodiscard]] bool ChannelBundle<T...>::dataAvailableImpl(std::index_sequence<Is...> /*unused*/) const
{
    const bool allChannelsAvailable = (at<Is>().dataAvailable() && ...);
    return allChannelsAvailable;
}

template <typename... T>
template <size_t... Is>
[[nodiscard]] bool ChannelBundle<T...>::dataAssignableImpl(std::index_sequence<Is...> /*unused*/) const
{
    const bool allChannelsAssignable = (at<Is>().dataAssignable() && ...);
    return allChannelsAssignable;
}

template <typename... T>
template <size_t... Is>
[[nodiscard]] size_t ChannelBundle<T...>::sizeImpl(std::index_sequence<Is...> /*unused*/) const
{
    if constexpr (sizeof...(Is) >= 1) {
        return std::min( { at<Is>().size()... });
    }

    return 0;
}

template <typename... T>
template <size_t... Is>
[[nodiscard]] size_t ChannelBundle<T...>::max_sizeImpl(std::index_sequence<Is...> /*unused*/) const
{
    if constexpr (sizeof...(Is) >= 1) {
        return std::min({ at<Is>().max_size()... });
    }

    return 0;
}

} // namespace df
