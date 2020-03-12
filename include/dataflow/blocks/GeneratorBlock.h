/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <atomic>
#include <chrono>
#include <future>

#include "../channels/ChannelBundle.h"
#include "../executors/ExecutorIf.h"
#include "BlockIf.h"
#include "outputPredicates/OutputAll.h"

using namespace std::literals::chrono_literals;
using namespace outputPredicates;
using namespace dataflow::channels;
using namespace dataflow::executors;

namespace dataflow::blocks {

constexpr size_t inf = 0;

///@cond internal
/**
 * @note
 * - Primary template for GeneratorBlock.
 * - Technical helper functions.
 * - Has no implementation.
 * - Implementation only by partial specialisations.
 * - The reason using a partial specialization for
 *   implementation is that only one template parameter pack is
 *   allowed to be used for primary templates. 
 */
template <typename OPERATOR, typename CHAN_BUNDLE_OUT, typename OUTPUT_PREDICATE = OutputAll>
class GeneratorBlock {
public:
    GeneratorBlock(OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/);
    GeneratorBlock(OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/, OUTPUT_PREDICATE /*unused*/);
};
/// @endcond internal

/**
 * @brief (Output-)Block
 *
 * @details
 * - Output block that periodically produces output data. 
 * - More general information about Blocks see @ref BlockIf.
 *
 * @tparam OPERATOR  Function kernel of the block
 * @tparam T_OUT...  Value types of the output data channels.
 * @tparam OUTPUT_PREDICATE Predicate to control output on the channels.
 *                          More information see
 *                          @ref dataflow::blocks::outputPredicates.
 */
template <typename OPERATOR, typename... T_OUT, typename OUTPUT_PREDICATE>
class GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>, OUTPUT_PREDICATE> : public BlockIf {

    static_assert(std::is_invocable_r_v<std::tuple<T_OUT...>, OPERATOR>,
        "Operator is not consistent with the input or/and output parameters!");

    static_assert(std::is_invocable_r_v<std::array<bool, sizeof...(T_OUT)>, OUTPUT_PREDICATE, const T_OUT&...>,
        "Output predicate is not consistent with the output parameters!");

public:
    GeneratorBlock(OPERATOR& op,
        ChannelBundle<T_OUT...> outputChannels,
        OUTPUT_PREDICATE outputPredicate = OutputAll {});

    template <class REP, class PERIOD>
    void start(
        std::chrono::duration<REP, PERIOD> period = 1000ms,
        std::chrono::duration<REP, PERIOD> offset = 0ms,
        size_t count = inf);

    void stop();
    void wait();

    void execute() override;
    [[nodiscard]] bool readyForExecution() const override;

private:
    template <class REP, class PERIOD>
    void executionLoop(
        std::chrono::duration<REP, PERIOD> period = 1000ms,
        std::chrono::duration<REP, PERIOD> offset = 0ms,
        size_t maxExecutions = inf);

    OPERATOR& op_;
    ChannelBundle<T_OUT...> outputChannels_;
    OUTPUT_PREDICATE outputPredicate_;

    template <size_t... Is>
    [[nodiscard]] std::array<bool, sizeof...(T_OUT)> evalOutputPredicate(const std::tuple<T_OUT...>& output,
        std::index_sequence<Is...> /*unused*/) const;

    size_t executions_ { 0 };
    size_t maxExecutions_ { 0 };

    std::future<void> executionHandle_;
    std::atomic_bool execute_;
};

} // namespace dataflow::blocks

#include "impl/GeneratorBlock.hpp"
