/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "Block.h"
#include "GeneratorBlock.h"
#include "OutputPredicate.h"
#include "SinkBlock.h"

/** @namespace dataflow::blocks
 *
 * @brief Functional entities of the dataflow framework. 
 *
 * @details
 * - Blocks are the functional objects in an dataflow
 *   network.
 * - A block can be attached to input- and/or
 *   output-channels and an invocable object the 
 *   block operator. 
 * - There are mainly three types of blocks, (Input-)Blocks,
 *   (Output-)Blocks and (Input-/Output-)Blocks.
 * - (Input-)Blocks only consume data, (Output-)Blocks only 
 *   generate data and (Input-/Output-)blocks are both consuming
 *   and generating data.
 */
namespace dataflow::blocks {

} // namespace dataflow::blocks
