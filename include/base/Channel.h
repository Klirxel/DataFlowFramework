#pragma once

#include <queue>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename T>
class Channel : public ChannelIf<T> {

public:
    constexpr void attachSinkBlock(BlockIf* /*block*/) noexcept override;
    constexpr void attachSourceBlock(BlockIf* /*block*/) noexcept override;
    T pop() override;
    void push(T&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;

private:
    inline void notify(BlockIf* /*block*/);

    BlockIf* sinkBlock_ {};
    BlockIf* sourceBlock_ {};
    std::queue<T> data_;
};

} // namespace df

#include "Channel.hpp"
