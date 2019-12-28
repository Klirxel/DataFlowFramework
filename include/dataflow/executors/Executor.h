#pragma once

#include "ExecutorIf.h"

namespace dataflow::executors {

class Executor : public ExecutorIf {

public:
    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
};

} //ns

#include "impl/Executor.hpp"
