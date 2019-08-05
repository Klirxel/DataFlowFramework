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

    [[nodiscard]] bool readyForExecution() const override;

    void execute() override;

private:

    [[nodiscard]] bool freeSourceCapacity() const;
    [[nodiscard]] bool freeSinkCapacity() const;
    [[nodiscard]] std::size_t sourceCapacity() const;
    [[nodiscard]] std::size_t sinkCapacity() const;

    ChannelBundle<T_IN...> inputChannels_;
    OPERATOR& op_;
    ChannelBundle<T_OUT...> outputChannels_;
    ExecutorIf& executor_;

    std::atomic_size_t tasksCurrentlyQueued_{0};
    std::mutex taskLock_;
};

} // namespace df

#include "Block.hpp"
