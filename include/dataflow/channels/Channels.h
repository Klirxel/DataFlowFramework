#pragma once

#include "Channel.h"
#include "ChannelCircleBuf.h"
#include "decorators/ChannelAlwaysDataAvailableDecorator.h"
#include "decorators/ChannelThreadSafetyDecorator.h"
#include "ignorePredicates/IgnoreDefaults.h"

/** @namespace dataflow::channels
 *
 * @brief Communication entities of the dataflow framework. 
 *
 * @details
 * - Channels are responsible for transporting data between the
 *   dataflow::blocks.   
* - ChannelIf is the interface that has to be used for implementing
 *   a channel.
 * - There are different kind of channels. For an overview have an
 *   look on ChannelIf.
 * - For connecting channels to a block a ChannelBundle has to been 
 *   used. ChannelBundle are proxy objects, that allow the connection
 *   of multiple channels to a block.
 * - Channels are using move semantic to transport data.
 * - The input-/output-order is specified by the channel.
 *   When not specified explicitly first-in/first-out data order
 *   is used.
 * - Multiple sink- and source-blocks can be attached to one 
 *   channel. Note that when using multiple sink- or source-blocks
 *   no dataflow control performed. The order of input- and output-
 *   data is therefore not specified.
 * - Channels are always buffers, to allow seperation between
 *   the processing time of the sink- and source-blocks.
 *   The buffer size is specified by the channel.
 */
namespace dataflow::channels {

template <typename T>
using ChannelThreadSafe = decorators::ChannelThreadSafetyDecorator<Channel<T>>;

template <typename T>
using ChannelThreadSafeNoTrigger = decorators::ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

template <typename T>
using ChannelThreadSafeIgnoreDefaults = decorators::ChannelThreadSafetyDecorator<Channel<T, TriggerPolicy::triggerAll, TriggerPolicy::triggerSink, ignorePredicates::IgnoreDefaults>>;

template <typename T>
using ChannelAlwaysDataAvailable = decorators::ChannelAlwaysDataAvailableDecorator<Channel<T>>;

template <typename T>
using ChannelAlwaysDataAvailableNoTrigger = decorators::ChannelAlwaysDataAvailableDecorator<Channel<T, TriggerPolicy::triggerNone, TriggerPolicy::triggerNone>>;

template <typename T>
using ChannelAdTs = decorators::ChannelThreadSafetyDecorator<ChannelAlwaysDataAvailable<T>>;

template <typename T, std::size_t Size>
using ChannelCircleBufThreadSafe = decorators::ChannelThreadSafetyDecorator<ChannelCircleBuf<T, Size>>;

} // namespace df
