#include "Executor.h"

namespace df::base {

inline void Executor::execute(std::function<void()> func)
{
    func();
}

} //ns
