/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <atomic>
#include <type_traits>

#include "../channels/ChannelBundle.h"
#include "../executors/ExecutorAsync.h"


namespace dataflow::blocks {

using namespace dataflow::channels;
using namespace dataflow::executors;

///@cond internal
/**
 * @note
 * - Primary template for the Sinkblock.
 * - Technical helper functions.
 * - Has no implementation.
 * - Implementation only by partial specialisations.
 * - The reason using a partial specialization for
 *   implementation is that only one template parameter pack is
 *   allowed to be used for primary templates. 
 */
template <typename CHAN_BUNDLE_IN, typename OPERATOR>
class SinkBlock {
public:
    SinkBlock(CHAN_BUNDLE_IN /*unused*/, OPERATOR& /*unused*/, ExecutorIf&);
};
///@endcond internal

/**
 * @brief (Input-)Block
 *
 * @details
 * - Default implementation of an input block.
 * - More general information about Blocks see @ref BlockIf.
 *
 * @tparam T_IN...   Value types of the input data channels.
 * @tparam OPERATOR  Function kernel of the block
 */
template <typename... T_IN, typename OPERATOR>
class SinkBlock<ChannelBundle<T_IN...>,
    OPERATOR> : public BlockIf {

public:
    SinkBlock(ChannelBundle<T_IN...> inputChannels, OPERATOR& op, ExecutorIf& executor);

    [[nodiscard]] bool readyForExecution() const override;

    void execute() override;

private:
    [[nodiscard]] bool freeSourceCapacity() const;
    [[nodiscard]] std::size_t sourceCapacity() const;

    ChannelBundle<T_IN...> inputChannels_;
    OPERATOR& op_;
    ExecutorIf& executor_;

    std::atomic_size_t tasksCurrentlyQueued_ { 0 };
    std::mutex taskLock_;
};

} // namespace dataflow::blocks

#include "impl/SinkBlock.hpp"
