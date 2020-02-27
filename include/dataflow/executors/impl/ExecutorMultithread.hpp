/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include "../ExecutorMultithread.h"

namespace dataflow::executors {

ExecutorMultithread::ExecutorMultithread(size_t threads, std::chrono::milliseconds inactivityBeforeDestruction)
    : inactivityBeforeDestruction_(inactivityBeforeDestruction)
{
    for (size_t i = 0; i < threads; ++i) {
        auto executionHandle = threadWorker_.getExecutionHandle();
        threadPool_.emplace_back(std::move(executionHandle));
    }
}

inline void ExecutorMultithread::execute(std::function<void(void)>&& task, std::mutex& taskLock)
{
    threadWorker_.addTask(std::forward<std::function<void(void)>>(task), &taskLock);
}

inline void ExecutorMultithread::start()
{
    threadWorker_.startExecution();
}

inline void ExecutorMultithread::stop()
{
    threadWorker_.stopExecution();

    for (auto& thread : threadPool_) {
        if (thread.joinable()) {
            thread.join();
        }
    };
}

inline ExecutorMultithread::~ExecutorMultithread()
{
    while (inactivityBeforeDestruction_.count() != 0 && threadWorker_.tasksWaitingForExecution() != 0) {
        std::this_thread::sleep_for(inactivityBeforeDestruction_);
    };

    stop();
}

} //namespace dataflow::executors
