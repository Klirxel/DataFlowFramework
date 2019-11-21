#pragma once

#include <atomic>
#include <chrono>
#include <future>

#include "../channels/ChannelBundle.h"
#include "../executors/ExecutorIf.h"
#include "BlockIf.h"

using namespace std::literals::chrono_literals;
using namespace dataflow::channels;
using namespace dataflow::executors;

namespace dataflow::blocks {

constexpr size_t inf = 0;

template <typename OPERATOR, typename CHAN_BUNDLE_OUT>
class GeneratorBlock {
public:
    GeneratorBlock(OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/);
};

template <typename OPERATOR, typename... T_OUT>
class GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>> : public BlockIf {

public:
    GeneratorBlock(OPERATOR& op, ChannelBundle<T_OUT...> outputChannels);

    void start(std::chrono::milliseconds period = 1000ms, std::chrono::milliseconds offset = 0ms, size_t count = inf);
    void stop();
    void wait();

    void execute() override;
    bool readyForExecution() const override;

private:
    void executionLoop(std::chrono::milliseconds period, std::chrono::milliseconds offset, size_t maxExecutions);

    OPERATOR& op_;
    ChannelBundle<T_OUT...> outputChannels_;

    size_t executions_ { 0 };
    size_t maxExecutions_ { 0 };

    std::future<void> executionHandle_;
    std::atomic_bool execute_;
};

} //ns

#include "GeneratorBlock.hpp"
