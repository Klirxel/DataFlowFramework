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
    bool dataAvailable() const override;
    bool dataAssignable() const override;

private:
    BlockIf* sinkBlock_ {};
    BlockIf* sourceBlock_ {};
    std::queue<T> data_;
};

inline void notify(BlockIf* /*block*/);

} // namespace df

#include "Channel.hpp"
