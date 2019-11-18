#pragma once

#include "ExecutorIf.h"

namespace df::base {

class Executor : public ExecutorIf {

public:
    inline void execute(std::function<void(void)> &&task, std::mutex& taskLock) override;
};

} //ns

#include "Executor.hpp"