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
    outputChannels_.attachSourceBlock(this);
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::readyForExecution() const
{
    return allInputChannelsHaveData() && allOutputChannelsCanTakeData();
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::allInputChannelsHaveData() const
{
    return allInputChannelsHaveDataImpl(std::index_sequence_for<T_IN...> {});
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::allOutputChannelsCanTakeData() const
{
    return allOutputChannelsCanTakeDataImpl(std::index_sequence_for<T_OUT...> {});
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
template <size_t... Is>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::allInputChannelsHaveDataImpl(std::index_sequence<Is...> /*unused*/) const
{
    const bool allInputDataAvailable = (inputChannels_.template at<Is>().dataAvailable() && ...);
    return allInputDataAvailable;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
template <size_t... Is>
bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::allOutputChannelsCanTakeDataImpl(std::index_sequence<Is...> /*unused*/) const
{
    const bool allOutputDataAssignable = (outputChannels_.template at<Is>().dataAssignable() && ...);
    return allOutputDataAssignable;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
void Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>>::execute()
{

    if (not readyForExecution()) {
        return;
    }

    auto operatingSequence = [&]() {
        std::tuple<T_IN...> input = inputChannels_.pop();
        std::tuple<T_OUT...> output = std::apply(op_, move(input));
        outputChannels_.push(std::move(output));
    };

    executor_.execute(operatingSequence);
}

} // namespace df
