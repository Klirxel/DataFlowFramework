/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <algorithm>
#include <utility>

#include "../ExecutorAsync.h"

using namespace std::literals::chrono_literals;

namespace dataflow::executors {

inline ExecutorAsync::ExecutorAsync(std::launch policy) noexcept
    : policy_(policy)
{
}

inline void ExecutorAsync::execute(std::function<void()>&& task, std::mutex& taskLock)
{
    if (stop_) {
        return;
    };

    auto taskWithLock = [task_ = std::move(task), &taskLock]() {
        std::lock_guard lock { taskLock };
        task_();
    };

    store(std::async(policy_, std::move(taskWithLock)));
}

inline void ExecutorAsync::store(std::future<void>&& future)
{
    {
        std::lock_guard<std::mutex> lock_guard { mutex_ };
        futures_.push_back(std::forward<std::future<void>>(future));
    }
    clean();
}

inline void ExecutorAsync::clean()
{
    invalidateReadyFutures();
    eraseInvalidFutures();
}

inline void ExecutorAsync::invalidateReadyFutures()
{
    std::lock_guard<std::mutex> lock_guard { mutex_ };

    auto getIfReady = [](std::future<void>& future) {
        if (future.valid() && std::future_status::ready == future.wait_for(0s)) {
            future.get();
        };
    };

    std::for_each(futures_.begin(), futures_.end(), getIfReady);
}

inline void ExecutorAsync::eraseInvalidFutures()
{
    std::lock_guard<std::mutex> lock_guard { mutex_ };

    auto eraseInvalidFuture = [&](auto& iter) {
        if (not iter->valid()) {
            iter
                = futures_.erase(iter);
            --iter;
        };
    };

    for (auto iter = futures_.begin(); iter != futures_.end(); ++iter) {
        eraseInvalidFuture(iter);
    };
}

inline void ExecutorAsync::wait()
{
    auto getIfValid = [](std::future<void>& future) {
        if (future.valid()) {
            future.wait();
        }
    };

    std::for_each(futures_.begin(), futures_.end(), getIfValid);
}

inline void ExecutorAsync::stop() noexcept
{
    stop_ = true;
}

} //ns
