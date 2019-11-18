#pragma once

#include <tuple>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <size_t SIZE>
struct AllTrue {

    [[nodiscard]] constexpr operator std::array<bool, SIZE>() const noexcept
    {
        auto array = std::array<bool, SIZE> {};
        array.fill(true);
        return array;
    };
};

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

    std::optional<std::tuple<T...>> pop();
    void push(std::tuple<T...>&& /*data*/, const std::array<bool, sizeof...(T)>& outputPredicate = AllTrue<sizeof...(T)> {});

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
    void pushImpl(std::tuple<T...>&& /*data*/, const std::array<bool, sizeof...(T)>& /*outputCtlr*/, std::index_sequence<Is...> /*unused*/);

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

} // namespace df

#include "ChannelBundle.hpp"