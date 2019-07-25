#include "Executor.h"

namespace df::base {

inline void Executor::execute(std::function<void()> task, std::mutex &taskLock)
{
    std::lock_guard lock{taskLock};
    task();
}

} //ns
