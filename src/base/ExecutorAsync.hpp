#include "ExecutorAsync.h"

namespace df::base {

constexpr ExecutorAsync::ExecutorAsync(std::launch policy) noexcept
    : policy_(policy)
{
}

inline void ExecutorAsync::execute(std::function<void()> func)
{
    std::future<void>
        executionHandle = std::async(policy_, func);

    executionHandle.wait();
}

inline void ExecutorAsync::start() noexcept {}
inline void ExecutorAsync::stop() noexcept {}

}
// namespace «namespace»
