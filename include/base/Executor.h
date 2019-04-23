#pragma once

#include "ExecutorIf.h"

namespace df::base {

class Executor : public ExecutorIf {

public:
    inline void execute(std::function<void(void)> /*func*/) override;
};

} //ns

#include "Executor.hpp"
