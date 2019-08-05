#pragma once

#include <atomic>
#include <chrono>
#include <future>

#include "BlockIf.h"
#include "ChannelBundle.h"
#include "ExecutorIf.h"

using namespace std::literals::chrono_literals;

namespace df::base {

constexpr size_t inf = 0;

template <typename OPERATOR, typename CHAN_BUNDLE_OUT>
class GeneratorBlock {
public:
    GeneratorBlock(OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/);
};

template <typename OPERATOR, typename... T_OUT>
class GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>> {

public:
    GeneratorBlock(OPERATOR& op, ChannelBundle<T_OUT...> outputChannels);

    void start(std::chrono::milliseconds period = 1000ms, std::chrono::milliseconds offset = 0ms, size_t count = inf);
    void stop();
    void wait();

private:
    void executionStep();
    void executionLoop(std::chrono::milliseconds period, std::chrono::milliseconds offset, size_t count);

    OPERATOR& op_;
    ChannelBundle<T_OUT...> outputChannels_;

    std::future<void> executionHandle_;
    std::atomic_bool execute_;
};

} //ns

#include "GeneratorBlock.hpp"
