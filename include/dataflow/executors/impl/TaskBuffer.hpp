/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "../internal/TaskBuffer.h"

namespace dataflow::executors::internal {

inline void TaskBuffer::addTask(std::function<void(void)>&& task, std::mutex* task_lock)
{

    std::lock_guard<std::mutex> lock { mutex_ };

    tasks_.push_back(TaskWithLock { std::move(task), task_lock });
}

std::function<void()> TaskBuffer::getTask()
{
    std::lock_guard<std::mutex> lock { mutex_ };
    std::function<void(void)> task {};

    if (not empty()) {
        task = std::move(tasks_.front().task);
        tasks_.pop_front();
    };

    return task;
}

TaskWithLock TaskBuffer::getNextReadyTask()
{
    std::lock_guard<std::mutex> lock { mutex_ };
    TaskWithLock taskWl {};

    auto lockTaskIfPossible = [](TaskWithLock& twl) {
        return twl.task_lock != nullptr ? twl.task_lock->try_lock() : true;
    };
    auto iter = std::find_if(tasks_.begin(), tasks_.end(), lockTaskIfPossible);

    if (iter != tasks_.end()) {
        taskWl = std::move(*iter);
        tasks_.erase(iter);
    };

    return taskWl;
}

bool TaskBuffer::executeTask()
{
    auto task = getTask();

    bool taskExecuted = false;

    if (task) {
        task();
        taskExecuted = true;
    }

    return taskExecuted;
}

bool TaskBuffer::executeNextReadyTask()
{
    TaskWithLock taskWl = getNextReadyTask();

    bool taskExecuted = false;

    if (taskWl.task) {
        taskWl.task();
        taskWl.task_lock->unlock();
        taskExecuted = true;
    }

    return taskExecuted;
}

[[nodiscard]] inline bool TaskBuffer::empty() const
{
    return tasks_.empty();
}

[[nodiscard]] inline size_t TaskBuffer::size() const
{
    return tasks_.size();
}

} // namespace dataflow::executors::internal
