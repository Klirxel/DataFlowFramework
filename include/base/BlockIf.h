#pragma once

namespace df::base {

class BlockIf {
public:
    virtual bool readyForExecution() const = 0;
    virtual void execute() = 0;
};

} // namespace df
