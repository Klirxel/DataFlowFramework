#pragma once

#include "BlockIf.h"

namespace df::base {

struct ExecutorIf {

public:
    virtual void execute(BlockIf&) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

} //ns
