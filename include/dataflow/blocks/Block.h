/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once


#include <array>
#include <type_traits>

#include "../channels/ChannelBundle.h"
#include "../executors/ExecutorAsync.h"
#include "outputPredicates/OutputAll.h"

using namespace outputPredicates;
using namespace dataflow::channels;
using namespace dataflow::executors;

namespace dataflow::blocks {

///@cond internal
/**
 * @note
 * - Primary template for block.
 * - Technical helper functions.
 * - Has no implementation.
 * - Implementation only by partial specialisations.
 * - The reason using a partial specialization for
 *   implementation is that only one template parameter pack is
 *   allowed to be used for primary templates. 
 */
template <typename CHAN_BUNDLE_IN, typename OPERATOR, typename CHAN_BUNDLE_OUT,
    typename OUTPUT_PREDICATE = OutputAll>
class Block {
public:
    Block(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/, ExecutorIf&);

    Block(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/, ExecutorIf&, OUTPUT_PREDICATE);
};
///@endcond internal

/**
 * @brief (Input-/Output-)Block
 *
 * @details
 * - Default implementation of an (Input-/Output-) block.
 * - More general information about Blocks see
 *   @ref dataflow::blocks.
 *
 * @tparam T_IN...   Value types of the input data channels.
 * @tparam OPERATOR  Function kernel of the block
 * @tparam T_OUT...  Value types of the output data channels.
 * @tparam OUTPUT_PREDICATE Predicate to control output on the channels.
 *                          More information see
 *                          @ref dataflow::blocks::outputPredicates.
 *
 */
template <typename... T_IN, typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
class Block<
    ChannelBundle<T_IN...>,
    OPERATOR,
    channels::ChannelBundle<T_OUT...>,
    OUTPUT_PREDICATE> : public BlockIf {

    static_assert(std::is_invocable_r_v<std::tuple<T_OUT...>, OPERATOR, T_IN&&...>,
        "Operator is not consistent with the input or/and output parameters!");

    static_assert(std::is_invocable_r_v<std::array<bool, sizeof...(T_OUT)>, OUTPUT_PREDICATE, const T_OUT&...>,
        "Output predicate is not consistent with the output parameters!");

public:
    Block(ChannelBundle<T_IN...> inputChannels,
        OPERATOR& op,
        ChannelBundle<T_OUT...> outputChannels,
        ExecutorIf& executor,
        OUTPUT_PREDICATE outputPredicate = OutputAll {});

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

} // namespace dataflow::blocks

#include "impl/Block.hpp"
