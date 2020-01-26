/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "../ExecutorSeq.h"

namespace dataflow::executors {

inline void ExecutorSeq::execute(std::function<void()>&& task, std::mutex& taskLock)
{
    std::lock_guard lock { taskLock };
    task();
}

} //namespace dataflow::executors
