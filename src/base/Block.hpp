#include "Block.h"

namespace df::base {

template <typename... T>
constexpr std::array<bool, sizeof...(T)> OutputAll::operator()([[maybe_unused]] const T&... /*unused*/) const
{
    auto array = std::array<bool, sizeof...(T)> {};
    array.fill(true);
    return array;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::Block(ChannelBundle<T_IN...> inputChannels, OPERATOR& op,
    ChannelBundle<T_OUT...> outputChannels, ExecutorIf& executor, OUTPUT_PREDICATE outputPredicate)
    : inputChannels_(std::move(inputChannels))
    , op_(op)
    , outputChannels_(std::move(outputChannels))
    , executor_(executor)
    , outputPredicate_(outputPredicate)
{
    inputChannels_.attachSinkBlock(this);
    outputChannels_.attachSourceBlock(this);
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
[[nodiscard]] bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::readyForExecution() const
{
    return freeSourceCapacity() && freeSinkCapacity();
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
[[nodiscard]] bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::freeSourceCapacity() const
{
    const bool freeSourceCapacity = sourceCapacity() > 0 ? true : false;
    return freeSourceCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
[[nodiscard]] bool Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::freeSinkCapacity() const
{
    const bool freeSinkCapacity = sinkCapacity() > 0 ? true : false;
    return freeSinkCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
[[nodiscard]] size_t Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::sourceCapacity() const
{
    const std::size_t sourceCapacity = inputChannels_.size() - tasksCurrentlyQueued_;
    return sourceCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
[[nodiscard]] size_t Block<ChannelBundle<T_IN...>, OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::sinkCapacity() const
{
    const std::size_t sinkCapacity = outputChannels_.max_size() - tasksCurrentlyQueued_;
    return sinkCapacity;
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
void Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::execute()
{
    auto task = [&]() {
        std::optional<std::tuple<T_IN...>> input = inputChannels_.pop();

        if (input.has_value()) {

            std::tuple<T_OUT...> output = std::apply(op_, move(input).value());

            const std::array<bool, sizeof...(T_OUT)> outputPredicate = outputPredicateImpl(output, std::index_sequence_for<T_OUT...> {});
            outputChannels_.push(std::move(output), outputPredicate);
        }

        --tasksCurrentlyQueued_;
    };

    ++tasksCurrentlyQueued_;
    executor_.execute(std::move(task), taskLock_);
}

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
template <size_t... Is>
std::array<bool, sizeof...(T_OUT)> Block<ChannelBundle<T_IN...>,
    OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE>::outputPredicateImpl(const std::tuple<T_OUT...>& output, std::index_sequence<Is...> /*unused*/)
{
    return outputPredicate_(std::get<Is>(output)...);
}

} // namespace df
