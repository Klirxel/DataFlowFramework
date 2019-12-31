#pragma once

#include "ExecutorIf.h"

namespace dataflow::executors {

/**
 * @brief Sequential executor.
 *
 * @details
 * - Sequential (not parallel) execution of tasks.
 * - No thread safe channels required. 
 */
class Executor : public ExecutorIf {

public:
    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
};

} //namespace dataflow::executors

#include "impl/Executor.hpp"
