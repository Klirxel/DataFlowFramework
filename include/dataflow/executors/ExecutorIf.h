/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <functional>
#include <mutex>

namespace dataflow::executors {

/**
 * @brief Generic interface for executors.
 *
 * @details
 * - Executors are assigned to dataflow::blocks.
 *
 */
struct ExecutorIf {

public:
    virtual void execute(std::function<void(void)>&& task, std::mutex& taskLock) = 0;
};

} // namespace dataflow::executors
