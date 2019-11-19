#include <future>

#include "GeneratorBlock.h"

namespace df::base {

template <typename OPERATOR, typename... T_OUT>
GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::GeneratorBlock(OPERATOR& op, ChannelBundle<T_OUT...> outputChannels)
    : op_(op)
    , outputChannels_(std::move(outputChannels))
    , execute_(false)
{
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>>::executionStep()
{
    std::tuple<T_OUT...> output = op_();
    outputChannels_.push(std::move(output));
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::executionLoop(std::chrono::milliseconds period, std::chrono::milliseconds offset, size_t count)
{
    std::this_thread::sleep_for(offset);
    size_t curCount = 0;

    while (execute_ && (count == inf or curCount++ < count)) {
        executionStep();
        std::this_thread::sleep_for(period);
    };
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::start(std::chrono::milliseconds period, std::chrono::milliseconds offset, size_t count)
{

    execute_ = true;

    auto execLoopAsyncWrapper = [&](auto period, auto offset, auto count) {
        executionLoop(period, offset, count);
    };

    executionHandle_ = std::async(std::launch::async, execLoopAsyncWrapper, period, offset, count);
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::stop()
{
    execute_ = false;
    executionHandle_.wait();
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::wait()
{
    executionHandle_.wait();
    execute_ = false;
}

}
// ns
