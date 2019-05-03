#pragma once

#include <tuple>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename... T>
class ChannelBundle {

public:
    template <size_t I>
    using ChannelValueType = std::tuple_element_t<I, std::tuple<T...>>;

    template <size_t I>
    using ChannelType = ChannelIf<ChannelValueType<I>>;
    constexpr ChannelBundle(ChannelIf<T>&... channels) noexcept;
    constexpr void attachSinkBlock(BlockIf* /*block*/) noexcept;
    constexpr void attachSourceBlock(BlockIf* /*block*/) noexcept;

    template <size_t I>
    constexpr ChannelType<I>& at() noexcept;

    template <size_t I>
    constexpr const ChannelType<I>& at() const noexcept;

    std::tuple<T...> pop();
    void push(std::tuple<T...>&& /*data*/);

private:
    template <size_t... Is>
    constexpr void attachSinkBlockImpl(BlockIf* block, std::index_sequence<Is...> /*unused*/) noexcept;

    template <size_t... Is>
    constexpr void attachSourceBlockImpl(BlockIf* block, std::index_sequence<Is...> /*unused*/) noexcept;

    template <size_t... Is>
    std::tuple<T...> popImpl(std::index_sequence<Is...> /*unused*/);

    template <size_t... Is>
    void pushImpl(std::tuple<T...>&& /*data*/, std::index_sequence<Is...> /*unused*/);

    std::tuple<ChannelIf<T>&...> channels_;
};

} // namespace df

#include "ChannelBundle.hpp"
