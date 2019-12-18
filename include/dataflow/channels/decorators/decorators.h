#pragma once

#include <type_traits>

#include "../blocks/BlockIf.h"
#include "ChannelIf.h"

using namespace dataflow::blocks;

namespace dataflow::channels {

template <class CHANNEL>
class ChannelAlwaysDataAvailableDecorator : public ChannelIf<typename CHANNEL::ValueType> {

public:
    using ValueType = typename CHANNEL::ValueType;

    static_assert(std::is_base_of_v<ChannelIf<ValueType>, CHANNEL>, "CHANNEL is not derived from ChannelIf<T>");
    static_assert(std::is_default_constructible_v<CHANNEL>, "CHANNEL is not default constructible.");
    static_assert(std::is_default_constructible_v<ValueType>, "ValueType is not default constructible.");

    void attachSinkBlock(BlockIf* /*block*/) override;
    void attachSourceBlock(BlockIf* /*block*/) override;

    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] constexpr std::size_t size() const override;
    [[nodiscard]] constexpr std::size_t max_size() const override;

private:
    CHANNEL chan_;
};

} // namespace df

#include "impl/ChannelAlwaysDataAvailableDecorator.hpp"
