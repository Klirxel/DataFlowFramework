#include "../SinkBlock.h"

namespace dataflow::blocks {

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
    return freeSourceCapacity();
}

template <typename... T_IN, typename OPERATOR>
void SinkBlock<ChannelBundle<T_IN...>,
    OPERATOR>::execute()
{

    auto task = [&]() {
        std::optional<std::tuple<T_IN...>> input = inputChannels_.pop();

        if (input.has_value()) {
            std::apply(op_, move(input).value());
        }

        --tasksCurrentlyQueued_;
    };

    executor_.execute(task, taskLock_);
    ++tasksCurrentlyQueued_;
}

template <typename... T_IN, typename OPERATOR>
[[nodiscard]] bool SinkBlock<ChannelBundle<T_IN...>, OPERATOR>::freeSourceCapacity() const
{
    return sourceCapacity() > 0;
}

template <typename... T_IN, typename OPERATOR>
[[nodiscard]] size_t SinkBlock<ChannelBundle<T_IN...>, OPERATOR>::sourceCapacity() const
{
    const std::size_t sourceCapacity = inputChannels_.size() - tasksCurrentlyQueued_;
    return sourceCapacity;
}

} // namespace df
