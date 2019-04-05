#pragma once

#include <type_traits>

#include "ChannelBundle.h"
#include "ExecutorAsync.h"

namespace df::base {

template <typename CHAN_BUNDLE_IN, typename OPERATOR, typename CHAN_BUNDLE_OUT>
class Block {
public:
    Block(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/, ExecutorIf&);
};

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
class Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>> : public BlockIf {

public:
    Block(ChannelBundle<T_IN...> inputChannels, OPERATOR& op, ChannelBundle<T_OUT...> outputChannels, ExecutorIf& executor);

    bool readyForExecution() const override;

    void execute() override;

private:
    template <size_t... Is>
    bool readyForExecutionImpl(std::index_sequence<Is...> /*unused*/) const;

    template <size_t... Is>
    std::tuple<T_OUT...> operateImpl(std::tuple<T_IN...> /*input*/, std::index_sequence<Is...> /*unused*/);

    ChannelBundle<T_IN...> inputChannels_;
    OPERATOR& op_;
    ChannelBundle<T_OUT...> outputChannels_;
    ExecutorIf& executor_;
};

} // namespace df

#include "Block.hpp"
