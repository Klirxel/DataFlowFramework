#pragma once

#include <atomic>
#include <future>
#include <list>
#include <mutex>

#include "ExecutorIf.h"

namespace df::base {

class ExecutorAsync : public ExecutorIf {

public:
    inline ExecutorAsync(std::launch policy = std::launch::deferred) noexcept;

    inline void execute(std::function<void(void)>&& task, std::mutex& taskLock) override;
    inline void wait();
    inline void stop() noexcept;

private:
    void store(std::future<void>&& /*future*/);
    inline void clean();
    inline void invalidateReadyFutures();
    inline void eraseInvalidFutures();

    std::atomic_bool stop_ { false };
    std::launch policy_;
    std::list<std::future<void>> futures_;
    mutable std::mutex mutex_;
};

} //ns

#include "ExecutorAsync.hpp"
