#pragma once

#include <memory>
#include <queue>
#include <type_traits>
#include <utility>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename T>
class Channel : public ChannelIf<T> {

public:
    void attachSinkBlock(BlockIf* /*block*/) override;
    T pop() override;
    void push(T&& /*data*/) override;
    bool empty() const override;

private:
    BlockIf* outputBlock_ {};
    std::queue<T> data_;
};

} // namespace df

#include "Channel.hpp"
