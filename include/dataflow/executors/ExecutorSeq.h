/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include "ExecutorIf.h"

namespace dataflow::executors {

/**
 * @brief Sequential executor.
 *
 * @details
 * - Sequential (not parallel) execution of tasks.
 * - No thread safe channels required. 
 */
class ExecutorSeq : public ExecutorIf {

public:
    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
};

} //namespace dataflow::executors

#include "impl/ExecutorSeq.hpp"
