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
[[nodiscard]] bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::readyForExecution() const
{
    return inputChannels_.dataAvailable() && outputChannels_.dataAssignable();
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
void Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>>::execute()
{

    if (not readyForExecution()) {
        return;
    }

    auto task = [&]() {
        if (not readyForExecution()) {
            return;
        }

        std::tuple<T_IN...> input = inputChannels_.pop();
        std::tuple<T_OUT...> output = std::apply(op_, move(input));
        outputChannels_.push(std::move(output));
    };

    executor_.execute(std::move(task), taskLock_);
}

} // namespace df
