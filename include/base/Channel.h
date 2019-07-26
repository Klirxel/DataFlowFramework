#pragma once

#include <queue>
#include <vector>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename T>
class Channel : public ChannelIf<T> {

public:
    constexpr void attachSinkBlock(BlockIf* /*block*/) noexcept override;
    constexpr void attachSourceBlock(BlockIf* /*block*/) noexcept override;
    std::optional<T> pop() override;
    void push(T&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;

private:
    template <typename InputIter>
    void notify(InputIter blockListBegin, InputIter blockListEnd);

    std::vector<BlockIf*> sinkBlockList_ {};
    std::vector<BlockIf*> sourceBlockList_ {};
    std::queue<T> data_;
};

} // namespace df

#include "Channel.hpp"
