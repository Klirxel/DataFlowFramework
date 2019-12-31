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

} //ns

#include "../impl/TaskBuffer.hpp"
