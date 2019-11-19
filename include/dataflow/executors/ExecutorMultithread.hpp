#include "ExecutorMultithread.h"

namespace dataflow::executors {

inline ExecutorMultithread::ExecutorMultithread(size_t threads)
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
            std::cout << "joined thread!" << std::endl;
            thread.join();
        }
    };
}

} //ns
