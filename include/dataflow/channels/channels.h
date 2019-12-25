#pragma once

#include "ChannelThreadSave.h"

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

} // namespace dataflow::channels
