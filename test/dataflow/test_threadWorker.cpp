#define BOOST_TEST_MODULE testThreadWorker
#define BOOST_TEST_DYN_LINK

#include <future>

#include <boost/test/unit_test.hpp>

#include <dataflow/executors/internal/ThreadWorker.h>

using namespace std::literals::chrono_literals;
using namespace dataflow::executors::internal;

struct ExampleTask {
    void operator()() noexcept
    {
        ++executed;
    }

    static void reset() noexcept
    {
        executed = 0;
    }

    inline static size_t executed { 0 };
};

BOOST_AUTO_TEST_CASE(DefaultCtor)
{
    const bool enable = false;
    BOOST_CHECK_NO_THROW(ThreadWorker { enable });
}

BOOST_AUTO_TEST_CASE(ThreadWorkerSyncScenario)
{
    const bool enable = false;
    std::mutex taskLock;
    ThreadWorker threadWorker { enable };
    ExampleTask exampleTask1;
    ExampleTask exampleTask2;

    //AddTask 1
    BOOST_CHECK_NO_THROW(threadWorker.addTask(exampleTask1, &taskLock));
    BOOST_CHECK_EQUAL(threadWorker.tasksWaitingForExecution(), 1);

    //AddTask 2
    BOOST_CHECK_NO_THROW(threadWorker.addTask(exampleTask2, &taskLock));
    BOOST_CHECK_EQUAL(threadWorker.tasksWaitingForExecution(), 2);

    //RunTasks
    BOOST_CHECK_NO_THROW(threadWorker.processAvailableTasks());
    BOOST_CHECK_EQUAL(ExampleTask::executed, 2);
    BOOST_CHECK_EQUAL(threadWorker.tasksWaitingForExecution(), 0);

    //Reset
    ExampleTask::reset();
}

BOOST_AUTO_TEST_CASE(ThreadWorkerAsyncScenario)
{
    const bool enable = false;
    std::mutex taskLock;
    ThreadWorker threadWorker { enable };

    auto future = std::async(std::launch::async, threadWorker.getExecutionHandle());

    ExampleTask exampleTask1;
    ExampleTask exampleTask2;

    //AddTask 1
    BOOST_CHECK_NO_THROW(threadWorker.addTask(exampleTask1, &taskLock));
    BOOST_CHECK_EQUAL(threadWorker.tasksWaitingForExecution(), 1);

    //AddTask 2
    BOOST_CHECK_NO_THROW(threadWorker.addTask(exampleTask2, &taskLock));
    BOOST_CHECK_EQUAL(threadWorker.tasksWaitingForExecution(), 2);

    //RunTasks
    threadWorker.startExecution();
    std::this_thread::sleep_for(100ms);

    //StopTasks
    threadWorker.stopExecution();
    BOOST_CHECK_EQUAL(ExampleTask::executed, 2);
    BOOST_CHECK_EQUAL(threadWorker.tasksWaitingForExecution(), 0);

    //Reset
    ExampleTask::reset();
}
