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
    return freeSourceCapacity() && freeSinkCapacity();
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
[[nodiscard]] bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::freeSourceCapacity() const
{
    const bool freeSourceCapacity = sourceCapacity() > 0 ? true : false;
    return freeSourceCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
[[nodiscard]] bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::freeSinkCapacity() const
{
    const bool freeSinkCapacity = sinkCapacity() > 0 ? true : false;
    return freeSinkCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
[[nodiscard]] size_t Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::sourceCapacity() const
{
    const std::size_t sourceCapacity = inputChannels_.size() - tasksCurrentlyQueued_;
    return sourceCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
[[nodiscard]] size_t Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>>::sinkCapacity() const
{
    const std::size_t sinkCapacity = outputChannels_.max_size() - tasksCurrentlyQueued_;
    return sinkCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT>
void Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>>::execute()
{

    if (not readyForExecution()) {
        return;
    }

    auto task = [&]() {
        std::optional<std::tuple<T_IN...>> input = inputChannels_.pop();

        if (input.has_value()) {

            //const std::array<bool,sizeof...(T_OUT)> outputCtrl = OutputPredicate{}(input.value());

            std::tuple<T_OUT...> output = std::apply(op_, move(input).value());

            //outputChannels_.push(std::move(output), outputCtrl);
            outputChannels_.push(std::move(output));
        }

        --tasksCurrentlyQueued_;
    };

    ++tasksCurrentlyQueued_;
    executor_.execute(std::move(task), taskLock_);
}
} // namespace df
