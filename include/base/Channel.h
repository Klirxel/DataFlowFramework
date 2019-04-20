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
    void attachSinkBlock(BlockIf* /*block*/) noexcept override;
    void attachSourceBlock(BlockIf* /*block*/) noexcept override;
    T pop() override;
    void push(T&& /*data*/) override;
    bool empty() const override;
    size_t size() const override;

private:
    BlockIf* sinkBlock_ {};
    BlockIf* sourceBlock_ {};
    std::queue<T> data_;
};

inline notify(BlockIf*);



} // namespace df

#include "Channel.hpp"
