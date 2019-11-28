#pragma once

#include <atomic>
#include <type_traits>

#include "../channels/ChannelBundle.h"
#include "../executors/ExecutorAsync.h"

using namespace dataflow::channels;
using namespace dataflow::executors;

namespace dataflow::blocks {

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
    [[nodiscard]] bool freeSourceCapacity() const;
    [[nodiscard]] std::size_t sourceCapacity() const;

    ChannelBundle<T_IN...> inputChannels_;
    OPERATOR& op_;
    ExecutorIf& executor_;

    std::atomic_size_t tasksCurrentlyQueued_ { 0 };
    std::mutex taskLock_;
};

} // namespace df

#include "impl/SinkBlock.hpp"
