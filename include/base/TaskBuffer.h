#pragma once

#include <deque>
#include <functional>
#include <mutex>
#include <thread>

namespace df::base {

struct TaskWithLock {
    std::function<void(void)> task;
    std::mutex* task_lock;
};

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

#include "TaskBuffer.hpp"
