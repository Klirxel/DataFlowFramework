/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "OutputAll.h"

/** @namespace dataflow::blocks::outputPredicates
 *  
 *  @brief Output predicates for Output-Blocks. 
 *         
 *  @details
 *  - Output predicates for Output-Blocks give you fine granular control
 *    if output on an (output-)channel should be performed.
 *  - Controlling is done for for each channel independently.
 *  - Decision is done by value analysis. 
 *  - One example is to hinder outputting data on  an channel when 
 *    the output data object is empty.
 *  - dataflow::blocks::outputPredicates::OutputAll is the reference output
 *    predicate that does output on every channel. 
 *  - Usage examples can be found in test_block.cpp,
 *    test_block_output_predicate.cpp
 *    and test_generatorBlock.cpp.  
 */
namespace dataflow::blocks::outputPredicates {

} // namespace dataflow::blocks::outputPredicates
