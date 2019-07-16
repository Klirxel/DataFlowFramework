#pragma once

#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace df::base {

class TaskBuffer {

public:
    inline void addTask(std::function<void(void)>&& task);

    inline std::function<void()> getTask();
    inline bool executeTask();

    [[nodiscard]] inline bool empty() const;
    [[nodiscard]] inline size_t size() const;

private:
    std::queue<std::function<void(void)>> tasks_;
    std::mutex mutex_;
};

} //ns

#include "TaskBuffer.hpp"
