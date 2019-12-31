#include "../ExecutorSeq.h"

namespace dataflow::executors {

inline void ExecutorSeq::execute(std::function<void()>&& task, std::mutex& taskLock)
{
    std::lock_guard lock { taskLock };
    task();
}

} //namespace dataflow::executors
