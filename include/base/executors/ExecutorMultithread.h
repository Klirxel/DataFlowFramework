#pragma once

#include <thread>

#include "ExecutorIf.h"
#include "ThreadWorker.h"

namespace df::base {

class ExecutorMultithread : public ExecutorIf {

public:
    inline ExecutorMultithread(size_t threads = 1);
    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
    inline void start();
    inline void stop();

private:
    ThreadWorker threadWorker_;
    std::vector<std::thread> threadPool_;
};

} //ns

#include "ExecutorMultithread.hpp"
