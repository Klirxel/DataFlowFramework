#include "ExecutorAsync.h"

namespace df::base {

ExecutorAsync::ExecutorAsync(std::launch policy)
    : policy_(policy)
{
}

void ExecutorAsync::execute(std::function<void()> func)
{
    std::future<void>
        executionHandle = std::async(policy_, func);

    executionHandle.wait();
}

void ExecutorAsync::start() {}
void ExecutorAsync::stop() {}

}
// namespace «namespace»
