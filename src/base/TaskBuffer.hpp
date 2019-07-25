#include "TaskBuffer.h"

namespace df::base {

inline void TaskBuffer::addTask(std::function<void(void)>&& task)
{
    std::lock_guard<std::mutex> lock { mutex_ };

    tasks_.push(std::move(task));
}

std::function<void()> TaskBuffer::getTask()
{
    std::lock_guard<std::mutex> lock { mutex_ };
    std::function<void(void)> task {};

    if (not empty()) {
        task = std::move(tasks_.front());
        tasks_.pop();
    };

    return task;
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

[[nodiscard]] inline bool TaskBuffer::empty() const
{
    return tasks_.empty();
}

[[nodiscard]] inline size_t TaskBuffer::size() const
{
    return tasks_.size();
}

} //ns
