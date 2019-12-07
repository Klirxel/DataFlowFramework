#pragma once

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

/**
 * @brief Generic interface for blocks.
 *
 * @remark
 * - Should be used as a generic interface to address blocks.
 */
class BlockIf {
public:
    [[nodiscard]] virtual bool readyForExecution() const = 0;
    virtual void execute() = 0;
};

} //namespace dataflow::blocks
