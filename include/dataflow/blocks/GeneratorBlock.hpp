#include <future>

#include "GeneratorBlock.h"

namespace dataflow::blocks {

template <typename OPERATOR, typename... T_OUT>
GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::GeneratorBlock(OPERATOR& op, ChannelBundle<T_OUT...> outputChannels)
    : op_(op)
    , outputChannels_(std::move(outputChannels))
    , execute_(false)
{
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>>::execute()
{
    std::tuple<T_OUT...> output = op_();
    outputChannels_.push(std::move(output));
}

template <typename OPERATOR, typename... T_OUT>
bool GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>>::readyForExecution() const
{
    return execute_ && (maxExecutions_ == inf or executions_ < maxExecutions_);
}

template <typename OPERATOR, typename... T_OUT>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>>::executionLoop(std::chrono::milliseconds period, std::chrono::milliseconds offset, size_t maxExecutions)
{
    maxExecutions_ = maxExecutions;

    std::this_thread::sleep_for(offset);

    while (readyForExecution()) {
        execute();
        ++executions_;
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
