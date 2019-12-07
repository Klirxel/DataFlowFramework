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
 * - There are mainly three types of blocks, 
 *   dataflow::blocks::Block, dataflow::blocks::GeneratorBlock,
 *   dataflow::blocks::SinkBlock.
 *   (Standard) blocks have input- and ouput-channels and
 *   are processing the input data to generate output data.
 *   GeneratorBlocks only have output channels
 *   and generate only data. SinkBlocks have only
 *   input channels and only consume data.
 *
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
