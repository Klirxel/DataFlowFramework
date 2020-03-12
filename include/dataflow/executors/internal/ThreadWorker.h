/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>

#include "TaskBuffer.h"

namespace dataflow::executors::internal {

/**
 * @details
 * - sequential executor meant for running 
 *   asynchronous in an separated thread.
 * - used by ExecutorMultithread. 
 */
class ThreadWorker {

public:
    inline explicit ThreadWorker(bool enable = true) noexcept;

    inline void addTask(std::function<void(void)>&& task, std::mutex* taskLock_);
    inline void triggerExecution() noexcept;
    inline void stopExecution() noexcept;
    inline void startExecution() noexcept;
    inline void processAvailableTasks();
    [[nodiscard]] inline std::function<void()> getExecutionHandle();

    [[nodiscard]] inline size_t tasksWaitingForExecution() const;

private:
    inline void run_();

    TaskBuffer taskBuffer_;
    std::condition_variable wakeUpCall_;
    std::mutex wakeUpMutex_;
    std::atomic_bool enabled_ { true };
};

} // namespace dataflow::executors::internal

#include "../impl/ThreadWorker.hpp"
