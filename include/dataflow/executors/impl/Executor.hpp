#include "../Executor.h"

namespace dataflow::executors {

inline void Executor::execute(std::function<void()>&& task, std::mutex& taskLock)
{
    std::lock_guard lock { taskLock };
    task();
}

} //ns
