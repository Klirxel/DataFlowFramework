#pragma once

#include <future>

#include "ExecutorIf.h"

namespace df::base {

class ExecutorAsync : public ExecutorIf {

public:
    constexpr ExecutorAsync(std::launch policy = std::launch::deferred) noexcept;

    inline void execute(std::function<void(void)> /*func*/) override;
    inline void start() noexcept override;
    inline void stop() noexcept override;

private:
    std::launch policy_;
};

} //ns

#include "ExecutorAsync.hpp"
