/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <tuple>

#include "../blocks/BlockIf.h"
#include "../channels/ChannelIf.h"

using namespace dataflow::blocks;
using namespace dataflow::channels;

namespace dataflow::channels {

/**
 * @brief Collection of channels.
 *
 * @details
 * - Necessary for attaching multiple channels to a block.
 */
template <typename... T>
class ChannelBundle {

public:
    template <size_t I>
    using ChannelValueType = std::tuple_element_t<I, std::tuple<T...>>;

    template <size_t I>
    using ChannelType = ChannelIf<ChannelValueType<I>>;
    constexpr explicit ChannelBundle(ChannelIf<T>&... channels) noexcept;
    constexpr void attachSinkBlock(BlockIf* block) noexcept;
    constexpr void attachSourceBlock(BlockIf* block) noexcept;

    template <size_t I>
    [[nodiscard]] constexpr ChannelType<I>& at() noexcept;

    template <size_t I>
    [[nodiscard]] constexpr const ChannelType<I>& at() const noexcept;

    std::optional<std::tuple<T...>> pop();
    void push(std::tuple<T...>&& data, const std::array<bool, sizeof...(T)>& outputToChan = std::array<bool, sizeof...(T)> {}.fill(true));

    [[nodiscard]] bool dataAvailable() const;
    [[nodiscard]] bool dataAssignable() const;
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::size_t max_size() const;

private:
    template <size_t... Is>
    constexpr void attachSinkBlockImpl(BlockIf* block, std::index_sequence<Is...> /*unused*/) noexcept;

    template <size_t... Is>
    constexpr void attachSourceBlockImpl(BlockIf* block, std::index_sequence<Is...> /*unused*/) noexcept;

    template <size_t... Is>
    std::optional<std::tuple<T...>> popImpl(std::index_sequence<Is...> /*unused*/);

    template <size_t... Is>
    void pushImpl(std::tuple<T...>&& data, const std::array<bool, sizeof...(T)>& outputToChan, std::index_sequence<Is...> /*unused*/);

    template <size_t... Is>
    [[nodiscard]] bool dataAvailableImpl(std::index_sequence<Is...> /*unused*/) const;

    template <size_t... Is>
    [[nodiscard]] bool dataAssignableImpl(std::index_sequence<Is...> /*unused*/) const;

    template <size_t... Is>
    [[nodiscard]] std::size_t sizeImpl(std::index_sequence<Is...> /*unused*/) const;

    template <size_t... Is>
    [[nodiscard]] std::size_t max_sizeImpl(std::index_sequence<Is...> /*unused*/) const;

    std::tuple<ChannelIf<T>&...> channels_;
};

} // namespace dataflow::channels

#include "impl/ChannelBundle.hpp"
