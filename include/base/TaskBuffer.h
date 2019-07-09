#pragma once

#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace df::base {

class TaskBuffer {

public:
    inline TaskBuffer(size_t maxNrOfTasks = 1);

    inline bool addTask(std::function<void(void)>&& task);

    inline std::function<void()> getTask();

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline bool full() const;

    constexpr void setMaxNrOfTasks(size_t maxNrOfTasks) noexcept;

private:
    size_t maxNrOfTasks_;
    std::queue<std::function<void(void)>> tasks_;
    std::mutex mutex_;
};

} //ns

#include "TaskBuffer.hpp"
