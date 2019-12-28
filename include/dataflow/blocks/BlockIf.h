#pragma once

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
