#pragma once

#include <future>

#include "ExecutorIf.h"

namespace df::base {

class ExecutorAsync : public ExecutorIf {

public:
    ExecutorAsync(std::launch policy = std::launch::deferred);

    void execute(std::function<void(void)> /*func*/) override;
    void start() override;
    void stop() override;

private:
    std::launch policy_;
};

}
// namespace «namespace»
