#include "TaskBuffer.h"

namespace df::base {

inline TaskBuffer::TaskBuffer(size_t maxNrOfTasks)
    : maxNrOfTasks_(maxNrOfTasks)
{
}

inline bool TaskBuffer::addTask(std::function<void(void)>&& task)
{
    std::lock_guard<std::mutex> lock { mutex_ };
    bool taskAdded { false };

    if (not full()) {
        tasks_.push(std::move(task));
        taskAdded = true;
    }

    return taskAdded;
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

[[nodiscard]] inline bool TaskBuffer::empty() const
{
    return tasks_.empty();
}

[[nodiscard]] inline bool TaskBuffer::full() const
{
    return tasks_.size() >= maxNrOfTasks_;
}

constexpr void TaskBuffer::setMaxNrOfTasks(size_t maxNrOfTasks) noexcept
{
    maxNrOfTasks_ = maxNrOfTasks;
}

} //ns
