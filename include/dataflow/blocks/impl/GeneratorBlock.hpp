#include <future>
#include <utility>

#include "../GeneratorBlock.h"

namespace dataflow::blocks {

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::GeneratorBlock(
    OPERATOR& op,
    ChannelBundle<T_OUT...> outputChannels,
    OUTPUT_PREDICATE outputPredicate)
    : op_(op)
    , outputChannels_(std::move(outputChannels))
    , outputPredicate_(outputPredicate)
    , execute_(false)
{
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
void GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::execute()
{
    std::tuple<T_OUT...> output = op_();
    const auto outputPredicate = evalOutputPredicate(output, std::index_sequence_for<T_OUT...> {});
    outputChannels_.push(std::move(output), outputPredicate);
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
bool GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::readyForExecution() const
{
    return execute_ && (maxExecutions_ == inf or executions_ < maxExecutions_);
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
template <class REP, class PERIOD>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::executionLoop(
    std::chrono::duration<REP, PERIOD> period,
    std::chrono::duration<REP, PERIOD> offset,
    size_t maxExecutions)
{
    maxExecutions_ = maxExecutions;

    std::this_thread::sleep_for(offset);

    while (readyForExecution()) {
        execute();
        ++executions_;
        std::this_thread::sleep_for(period);
    };
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
template <class REP, class PERIOD>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::start(
    std::chrono::duration<REP, PERIOD> period,
    std::chrono::duration<REP, PERIOD> offset,
    size_t count)
{
    execute_ = true;

    auto execLoopAsyncWrapper = [&](auto period, auto offset, auto count) {
        executionLoop(period, offset, count);
    };

    executionHandle_ = std::async(std::launch::async, execLoopAsyncWrapper, period, offset, count);
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::stop()
{
    execute_ = false;
    executionHandle_.wait();
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
void GeneratorBlock<OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::wait()
{
    executionHandle_.wait();
    execute_ = false;
}

template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
template <size_t... Is>
[[nodiscard]] std::array<bool, sizeof...(T_OUT)> GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::evalOutputPredicate(const std::tuple<T_OUT...>& output,
    std::index_sequence<Is...> /*unused*/) const
{
    return outputPredicate_(std::get<Is>(output)...);
}

} // namespace dataflow::blocks
// ns
