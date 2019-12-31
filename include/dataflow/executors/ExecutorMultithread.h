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
    inline ExecutorMultithread(size_t threads = 1);
    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
    inline void start();
    inline void stop();

private:
    internal::ThreadWorker threadWorker_;
    std::vector<std::thread> threadPool_;
};

} //namespace dataflow::executors

#include "impl/ExecutorMultithread.hpp"
