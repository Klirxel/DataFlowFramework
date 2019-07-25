#pragma once

#include <type_traits>

#include "ChannelBundle.h"
#include "ExecutorAsync.h"

namespace df::base {

template <typename CHAN_BUNDLE_IN, typename OPERATOR>
class SinkBlock {
public:
    SinkBlock(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, ExecutorIf&);
};

template <typename... T_IN, typename OPERATOR>
class SinkBlock<ChannelBundle<T_IN...>,
    OPERATOR> : public BlockIf {

public:
    SinkBlock(ChannelBundle<T_IN...> inputChannels, OPERATOR& op, ExecutorIf& executor);

    bool readyForExecution() const override;

    void execute() override;

private:
    template <size_t... Is>
    bool readyForExecutionImpl(std::index_sequence<Is...> /*unused*/) const;

    ChannelBundle<T_IN...> inputChannels_;
    OPERATOR& op_;
    ExecutorIf& executor_;

    std::mutex taskLock_;
};

} // namespace df

#include "SinkBlock.hpp"
