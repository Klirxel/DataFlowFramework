/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <atomic>
#include <future>
#include <list>
#include <mutex>

#include "ExecutorIf.h"

namespace dataflow::executors {

/**
 * @brief Async executor.
 *
 * @details
 * - Asynchronous execution of tasks.
 * - Does require thread safe channels.
 * - Used std::async for implementation.
 */
class ExecutorAsync : public ExecutorIf {

public:
    inline explicit ExecutorAsync(std::launch policy = std::launch::deferred) noexcept;

    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
    inline void wait();
    inline void stop() noexcept;

private:
    void store(std::future<void>&& future);
    inline void clean();
    inline void invalidateReadyFutures();
    inline void eraseInvalidFutures();

    std::atomic_bool stop_ { false };
    std::launch policy_;
    std::list<std::future<void>> futures_;
    mutable std::mutex mutex_;
};

} // namespace dataflow::executors

#include "impl/ExecutorAsync.hpp"
