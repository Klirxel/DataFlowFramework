/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <thread>

#include "ExecutorIf.h"
#include "internal/ThreadWorker.h"

namespace dataflow::executors {

/**
 * @brief Multithread executor
 *
 * @details
 * - parallel execution of tasks.
 * - thread safe channels required.
 * - uses a customized thread pool and  
 *   task-scheduler.
 */
class ExecutorMultithread : public ExecutorIf {

public:
    inline explicit ExecutorMultithread(size_t threads = 1,
        std::chrono::milliseconds inactivityBeforeDestruction = 0ms);

    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
    inline void start();
    inline void stop();

    ExecutorMultithread(const ExecutorMultithread& other) = delete;
    ExecutorMultithread(ExecutorMultithread&& other) = delete;
    ExecutorMultithread& operator=(ExecutorMultithread& other) = delete;
    ExecutorMultithread& operator=(ExecutorMultithread&& other) = delete;

    inline ~ExecutorMultithread();

private:
    internal::ThreadWorker threadWorker_;
    std::vector<std::thread> threadPool_;
    std::chrono::milliseconds inactivityBeforeDestruction_;
};

} //namespace dataflow::executors

#include "impl/ExecutorMultithread.hpp"
