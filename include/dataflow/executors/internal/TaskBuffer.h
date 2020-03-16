/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <deque>
#include <functional>
#include <mutex>
#include <thread>

namespace dataflow::executors::internal {

struct TaskWithLock {
    std::function<void(void)> task;
    std::mutex* task_lock;
};

/**
 * @details
 * - container used for storing tasks.
 * - used by ThreadWorker.
 */
class TaskBuffer {

public:
    inline void addTask(std::function<void(void)>&& task, std::mutex* task_lock = nullptr);

    inline std::function<void()> getTask();
    inline TaskWithLock getNextReadyTask();
    inline bool executeTask();
    inline bool executeNextReadyTask();

    [[nodiscard]] inline bool empty() const;
    [[nodiscard]] inline size_t size() const;

private:
    std::deque<TaskWithLock> tasks_;
    std::mutex mutex_;
};

} // namespace dataflow::executors::internal

#include "../impl/TaskBuffer.hpp"
