#pragma once

#include <optional>
#include <type_traits>
#include <vector>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename ValueType>
struct ChannelDataContainerIf {

    virtual std::optional<ValueType> pop() = 0;
    virtual void push(ValueType&& /*data*/) = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual std::size_t max_size() const = 0;
};

template <template <typename> class ChannelDataContainer, typename ValueType>
class ChannelBase : public ChannelIf<ValueType> {

    static_assert(std::is_base_of_v<ChannelDataContainerIf<ValueType>, ChannelDataContainer<ValueType>>);

public:
    constexpr void attachSinkBlock(BlockIf* /*block*/) noexcept override;
    constexpr void attachSourceBlock(BlockIf* /*block*/) noexcept override;
    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    template <typename InputIter>
    void notify(InputIter blockListBegin, InputIter blockListEnd);

    std::vector<BlockIf*> sinkBlockList_ {};
    std::vector<BlockIf*> sourceBlockList_ {};
    ChannelDataContainer<ValueType> dataContainer_;
};

} // namespace df

#include "ChannelBase.hpp"
