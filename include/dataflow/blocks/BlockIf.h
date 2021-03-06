/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

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
