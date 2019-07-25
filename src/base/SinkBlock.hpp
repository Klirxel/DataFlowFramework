#include "SinkBlock.h"

namespace df::base {

template <typename... T_IN, typename OPERATOR>
SinkBlock<ChannelBundle<T_IN...>, OPERATOR>::SinkBlock(ChannelBundle<T_IN...> inputChannels, OPERATOR& op, ExecutorIf& executor)
    : inputChannels_(std::move(inputChannels))
    , op_(op)
    , executor_(executor)
{
    inputChannels_.attachSinkBlock(this);
}

template <typename... T_IN, typename OPERATOR>
bool SinkBlock<ChannelBundle<T_IN...>, OPERATOR>::readyForExecution() const
{
    return readyForExecutionImpl(std::index_sequence_for<T_IN...>());
}

template <typename... T_IN, typename OPERATOR>
template <size_t... Is>
bool SinkBlock<ChannelBundle<T_IN...>, OPERATOR>::readyForExecutionImpl(std::index_sequence<Is...> /*unused*/) const
{
    const bool allInputDataAvailable = (inputChannels_.template at<Is>().dataAvailable() && ...);
    return allInputDataAvailable;
}

template <typename... T_IN, typename OPERATOR>
void SinkBlock<ChannelBundle<T_IN...>,
    OPERATOR>::execute()
{

    if (not readyForExecution()) {
        return;
    }

    auto operatingSequence = [&]() {
        if (not readyForExecution()) {
            return;
        }
        std::tuple<T_IN...> input = inputChannels_.pop();
        std::apply(op_, move(input));
    };

    executor_.execute(operatingSequence);
}

} // namespace df
