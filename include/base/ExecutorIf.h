#pragma once

#include <functional>

#include "BlockIf.h"
#include "mutex"

namespace df::base {

struct ExecutorIf {

public:
    virtual void execute(std::function<void(void)> task, std::mutex& taskLock) = 0;
};

} //ns
