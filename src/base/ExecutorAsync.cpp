#include "ExecutorAsync.h"

namespace df::base {

ExecutorAsync::ExecutorAsync(std::launch policy)
    : policy_(policy)
{
}

void ExecutorAsync::execute(BlockIf& block)
{
    auto executeBlock = [](BlockIf* block) {
        block->execute();
    };

    std::future<void>
        executionHandle = std::async(policy_, executeBlock, &block);

    executionHandle.wait();
}

void ExecutorAsync::start() {}
void ExecutorAsync::stop() {}

}
// namespace «namespace»
