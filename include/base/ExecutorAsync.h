#pragma once

#include <future>

#include "ExecutorIf.h"

namespace df::base {

struct ExecutorAsync : public ExecutorIf {

public:
    ExecutorAsync(std::launch policy = std::launch::deferred);

    void execute(BlockIf& /*block*/) override;
    void start() override;
    void stop() override;

private:
    std::launch policy_;
};

}
// namespace «namespace»
