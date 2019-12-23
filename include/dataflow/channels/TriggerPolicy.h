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
