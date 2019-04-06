#include "Block.h"

namespace df::base {

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::Block(ChannelBundle<T_IN...> inputChannels, OPERATOR& op,
    ChannelBundle<T_OUT...> outputChannels, ExecutorIf& executor)
    : inputChannels_(std::move(inputChannels))
    , op_(op)
    , outputChannels_(std::move(outputChannels))
    , executor_(executor)
{
    inputChannels_.attachSinkBlock(this);
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::readyForExecution() const
{
    return readyForExecutionImpl(std::index_sequence_for<T_IN...>());
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
template <size_t... Is>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::readyForExecutionImpl(std::index_sequence<Is...> /*unused*/) const
{
    const bool chanInHasEmptyElem = (inputChannels_.template at<Is>().empty() || ...);
    return not chanInHasEmptyElem;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
void Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>>::execute()
{
    auto operatingSequence  = [&]() {
        std::tuple<T_IN...> input = inputChannels_.pop();
        std::tuple<T_OUT...> output = std::apply(op_, move(input));
        outputChannels_.push(std::move(output));
    };

    executor_.execute(operatingSequence);
}


} // namespace df
