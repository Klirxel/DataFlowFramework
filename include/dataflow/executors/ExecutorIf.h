#pragma once

#include <functional>

#include "../blocks/BlockIf.h"
#include "mutex"

using namespace dataflow::blocks;

namespace dataflow::executors {

struct ExecutorIf {

public:
    virtual void execute(std::function<void(void)>&& task, std::mutex& taskLock) = 0;
};

} //ns
