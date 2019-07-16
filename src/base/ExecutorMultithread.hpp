#include "ExecutorMultithread.h"

namespace df::base {

inline ExecutorMultithread::ExecutorMultithread(size_t threads) noexcept
    : threadPool_ { threads, std::thread { threadWorker_.getExecutionHandle() } }
{
}

inline void ExecutorMultithread::execute(std::function<void(void)> task)
{
    threadWorker_.addTask(std::move(task));
}

inline void ExecutorMultithread::start()
{
    threadWorker_.startExecution();
}

inline void ExecutorMultithread::stop()
{
    threadWorker_.stopExecution();

    for (auto& thread : threadPool_) {
        thread.join();
    };
}

} //ns

#include "ExecutorAsync.hpp"
