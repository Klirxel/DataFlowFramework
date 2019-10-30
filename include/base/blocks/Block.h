#pragma once

#include <type_traits>

#include "ChannelBundle.h"
#include "ExecutorAsync.h"

namespace df::base {

struct OutputAll {
    template <typename... T>
    [[nodiscard]] constexpr std::array<bool, sizeof...(T)> operator()([[maybe_unused]] const T&... /*unused*/) const;
};

template <typename CHAN_BUNDLE_IN, typename OPERATOR, typename CHAN_BUNDLE_OUT,
    typename OUTPUT_PREDICATE = OutputAll>
class Block {
public:
    Block(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/, ExecutorIf&);

    Block(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/, ExecutorIf&, OUTPUT_PREDICATE);
};

template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
class Block<
    ChannelBundle<T_IN...>,
    OPERATOR,
    ChannelBundle<T_OUT...>,
    OUTPUT_PREDICATE> : public BlockIf {

public:
    Block(ChannelBundle<T_IN...> inputChannels,
        OPERATOR& op,
        ChannelBundle<T_OUT...> outputChannels,
        ExecutorIf& executor,
        OUTPUT_PREDICATE outputPredicate = OutputAll{});

    [[nodiscard]] bool readyForExecution() const override;

    void execute() override;

private:
    [[nodiscard]] bool freeSourceCapacity() const;
    [[nodiscard]] bool freeSinkCapacity() const;
    [[nodiscard]] std::size_t sourceCapacity() const;
    [[nodiscard]] std::size_t sinkCapacity() const;

    template <size_t... Is>
    std::array<bool, sizeof...(T_OUT)> outputPredicateImpl(const std::tuple<T_OUT...>& output, std::index_sequence<Is...> /*unused*/);                                                    
    ChannelBundle<T_IN...> inputChannels_;
    OPERATOR& op_;
    ChannelBundle<T_OUT...> outputChannels_;
    ExecutorIf& executor_;
    OUTPUT_PREDICATE outputPredicate_;

    std::atomic_size_t tasksCurrentlyQueued_ { 0 };
    std::mutex taskLock_;
};

} // namespace df

#include "Block.hpp"
