#include "ThreadWorker.h"

namespace df::base {

inline ThreadWorker::ThreadWorker(bool enable) noexcept
    : enabled_ { enable }
{
}

inline void ThreadWorker::run_()
{
    while (enabled_) {
        processAvailableTasks();

        if (enabled_) {
            std::unique_lock<std::mutex> alarm(wakeUpMutex_);
            wakeUpCall_.wait(alarm);
        }
    };
}

[[nodiscard]] inline std::function<void()> ThreadWorker::getExecutionHandle()
{
    auto worker = [this] {
        this->run_();
    };

    return worker;
}

inline void ThreadWorker::processAvailableTasks()
{
    while (taskBuffer_.executeTask()) {
    };
}

inline void ThreadWorker::addTask(std::function<void(void)>&& task)
{
    taskBuffer_.addTask(std::move(task));
    triggerExecution();
}

inline void ThreadWorker::triggerExecution() noexcept
{
    wakeUpCall_.notify_one();
}

inline void ThreadWorker::stopExecution() noexcept
{
    enabled_ = false;
    wakeUpCall_.notify_all();
}

inline void ThreadWorker::startExecution() noexcept
{
    enabled_ = true;
    triggerExecution();
}

[[nodiscard]] inline size_t ThreadWorker::tasksWaitingForExecution() const
{
    return taskBuffer_.size();
}

} //ns
