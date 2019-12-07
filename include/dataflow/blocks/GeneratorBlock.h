#pragma once

#include <atomic>
#include <chrono>
#include <future>

#include "../channels/ChannelBundle.h"
#include "../executors/ExecutorIf.h"
#include "BlockIf.h"

using namespace std::literals::chrono_literals;
using namespace dataflow::channels;
using namespace dataflow::executors;

namespace dataflow::blocks {

constexpr size_t inf = 0;

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
template <typename OPERATOR, typename CHAN_BUNDLE_OUT>
class GeneratorBlock {
public:
    GeneratorBlock(OPERATOR& /*unused*/, CHAN_BUNDLE_OUT /*unused*/);
};

/**
 * @brief (Output-)Block
 *
 * @details
 * - Output block that periodically produces output data. 
 * - More general information about Blocks see @ref BlockIf.
 *
 * @tparam OPERATOR  Function kernel of the block
 * @tparam T_OUT...  Value types of the output data channels.
 *
 */
template <typename OPERATOR, typename... T_OUT>
class GeneratorBlock<
    OPERATOR, ChannelBundle<T_OUT...>> : public BlockIf {

    static_assert(std::is_invocable_r_v<std::tuple<T_OUT...>, OPERATOR>,
        "Operator is not consistent with the input or/and output parameters!");

public:
    GeneratorBlock(OPERATOR& op, ChannelBundle<T_OUT...> outputChannels);

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

    size_t executions_ { 0 };
    size_t maxExecutions_ { 0 };

    std::future<void> executionHandle_;
    std::atomic_bool execute_;
};

} //ns

#include "impl/GeneratorBlock.hpp"
