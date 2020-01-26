/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

namespace dataflow::channels {

/**
 * @brief Control trigger policy of an channel.
 *
 * @details
 * - Controls weather source- or/and sink-blocks are 
 *   triggered when data is pushed or popped from an
 *   channel. 
 */
enum class TriggerPolicy {
    triggerSink,
    triggerSource,
    triggerAll,
    triggerNone
};

} // namespace dataflow::channels
