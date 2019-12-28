#pragma once

#include <functional>
#include <mutex>

namespace dataflow::executors {

/**
 * @brief Generic interface for executors.
 *
 * @details
 * - Executors are assigned to dataflow::blocks.
 *
 */
struct ExecutorIf {

public:
    virtual void execute(std::function<void(void)>&& task, std::mutex& taskLock) = 0;
};

} //namespace dataflow::blocks
