#pragma once

#include <functional>

#include "BlockIf.h"

namespace df::base {

struct ExecutorIf {

public:
    virtual void execute(std::function<void(void)>) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

} //ns
