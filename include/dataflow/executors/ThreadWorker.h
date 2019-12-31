#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>

#include "internal/TaskBuffer.h"

namespace dataflow::executors {

class ThreadWorker {

public:
    inline ThreadWorker(bool enable = true) noexcept;

    inline void addTask(std::function<void(void)>&& task, std::mutex* taskLock_);
    inline void triggerExecution() noexcept;
    inline void stopExecution() noexcept;
    inline void startExecution() noexcept;
    inline void processAvailableTasks();
    [[nodiscard]] inline std::function<void()> getExecutionHandle();

    [[nodiscard]] inline size_t tasksWaitingForExecution() const;

private:
    inline void run_();

    TaskBuffer taskBuffer_;
    std::condition_variable wakeUpCall_;
    std::mutex wakeUpMutex_;
    std::atomic_bool enabled_ { true };
};

} //namespace dataflow::executors

#include "impl/ThreadWorker.hpp"
