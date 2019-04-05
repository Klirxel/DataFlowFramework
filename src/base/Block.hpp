#include "Block.h"

namespace df::base {

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::Block(ChannelBundle<T_IN...> inputChannels, OPERATOR& op,
    ChannelBundle<T_OUT...> outputChannels)
    : inputChannels_(std::move(inputChannels))
    , op_(op)
    , outputChannels_(std::move(outputChannels))
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
    std::tuple<T_IN...> input = inputChannels_.pop();
    std::tuple<T_OUT...> output = operateImpl(std::move(input), std::index_sequence_for<T_IN...>());
    outputChannels_.push(std::move(output));
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
template <size_t... Is>
std::tuple<T_OUT...> Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>>::operateImpl(std::tuple<T_IN...> input, std::index_sequence<Is...> /*unused*/)
{
    return op_(std::move(std::get<Is>(input))...);
}

} // namespace df
