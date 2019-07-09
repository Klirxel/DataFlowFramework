#define BOOST_TEST_MODULE testTaskBuffer
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "TaskBuffer.h"

using namespace df::base;

BOOST_AUTO_TEST_CASE(DefaultCtor)
{
    BOOST_CHECK_NO_THROW(TaskBuffer {});
}

BOOST_AUTO_TEST_CASE(DefaultCtorBehaviour)
{
    TaskBuffer taskBuffer {};

    BOOST_CHECK_EQUAL(taskBuffer.empty(), true);
    BOOST_CHECK_EQUAL(taskBuffer.full(), false);
}

BOOST_AUTO_TEST_CASE(AddTask)
{
    TaskBuffer taskBuffer {};
    auto task = [] {};

    BOOST_CHECK_NO_THROW(taskBuffer.addTask(task));

    BOOST_CHECK_EQUAL(taskBuffer.empty(), false);
    BOOST_CHECK_EQUAL(taskBuffer.full(), true);
}

BOOST_AUTO_TEST_CASE(GetTask)
{
    TaskBuffer taskBuffer {};
    int taskCalls = 0;
    auto inputTask = [&taskCalls] { ++taskCalls; };
    taskBuffer.addTask(inputTask);

    std::function<void()> outputTask;
    BOOST_CHECK_NO_THROW(outputTask = taskBuffer.getTask());

    outputTask();
    BOOST_CHECK_EQUAL(taskCalls, 1);
}

BOOST_AUTO_TEST_CASE(SetMaxNrOfTasks)
{
    TaskBuffer taskBuffer { 0 };
    BOOST_CHECK_EQUAL(taskBuffer.empty(), true);
    BOOST_CHECK_EQUAL(taskBuffer.full(), true);

    taskBuffer.setMaxNrOfTasks(1);
    BOOST_CHECK_EQUAL(taskBuffer.empty(), true);
    BOOST_CHECK_EQUAL(taskBuffer.full(), false);
}

BOOST_AUTO_TEST_CASE(GetSetMultipleTasks)
{
    const size_t maxNrOfTasks = 2;
    TaskBuffer taskBuffer { maxNrOfTasks };
    int task1Calls = 0;
    int task2Calls = 0;
    auto inputTask1 = [&task1Calls] { ++task1Calls; };
    auto inputTask2 = [&task2Calls] { ++task2Calls; };

    //Test 1: put in two values
    BOOST_CHECK_EQUAL(taskBuffer.addTask(inputTask1), true);
    BOOST_CHECK_EQUAL(taskBuffer.addTask(inputTask2), true);

    BOOST_CHECK_EQUAL(taskBuffer.empty(), false);
    BOOST_CHECK_EQUAL(taskBuffer.full(), true);

    //Test 2: check full behaviour
    BOOST_CHECK_EQUAL(taskBuffer.addTask(std::function<void()> {}), false);

    //Test 3: get first task back
    std::function<void()> outputTask1;
    BOOST_CHECK_NO_THROW(outputTask1 = taskBuffer.getTask());
    BOOST_CHECK_EQUAL(taskBuffer.empty(), false);
    BOOST_CHECK_EQUAL(taskBuffer.full(), false);
    outputTask1();
    BOOST_CHECK_EQUAL(task1Calls, 1);

    //Test 4: get second task back
    std::function<void()> outputTask2;
    BOOST_CHECK_NO_THROW(outputTask2 = taskBuffer.getTask());
    BOOST_CHECK_EQUAL(taskBuffer.empty(), true);
    BOOST_CHECK_EQUAL(taskBuffer.full(), false);
    outputTask2();
    BOOST_CHECK_EQUAL(task2Calls, 1);
}
