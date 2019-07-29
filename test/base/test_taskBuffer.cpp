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
    BOOST_CHECK_EQUAL(taskBuffer.size(), 0);
}

BOOST_AUTO_TEST_CASE(AddTask)
{
    TaskBuffer taskBuffer {};
    auto task = [] {};
    std::mutex task_lock;

    BOOST_CHECK_NO_THROW(taskBuffer.addTask(task, &task_lock));

    BOOST_CHECK_EQUAL(taskBuffer.empty(), false);
    BOOST_CHECK_EQUAL(taskBuffer.size(), 1);
}
BOOST_AUTO_TEST_CASE(GetTask)
{
    TaskBuffer taskBuffer {};
    std::mutex task_lock;
    int taskCalls = 0;
    auto inputTask = [&taskCalls] { ++taskCalls; };
    taskBuffer.addTask(inputTask, &task_lock);

    std::function<void()> outputTask;
    BOOST_CHECK_NO_THROW(outputTask = taskBuffer.getTask());

    outputTask();
    BOOST_CHECK_EQUAL(taskCalls, 1);
}

BOOST_AUTO_TEST_CASE(GetSetMultipleTasks)
{
    TaskBuffer taskBuffer {};
    std::mutex task_lock;

    int task1Calls = 0;
    int task2Calls = 0;
    auto inputTask1 = [&task1Calls] { ++task1Calls; };
    auto inputTask2 = [&task2Calls] { ++task2Calls; };

    //Test 1: put in two values
    BOOST_CHECK_NO_THROW(taskBuffer.addTask(inputTask1, &task_lock));
    BOOST_CHECK_NO_THROW(taskBuffer.addTask(inputTask2, &task_lock));

    BOOST_CHECK_EQUAL(taskBuffer.empty(), false);
    BOOST_CHECK_EQUAL(taskBuffer.size(), 2);

    //Test 2: get first task back
    std::function<void()> outputTask1;
    BOOST_CHECK_NO_THROW(outputTask1 = taskBuffer.getTask());
    BOOST_CHECK_EQUAL(taskBuffer.empty(), false);
    BOOST_CHECK_EQUAL(taskBuffer.size(), 1);
    outputTask1();
    BOOST_CHECK_EQUAL(task1Calls, 1);

    //Test 3: get second task back
    std::function<void()> outputTask2;
    BOOST_CHECK_NO_THROW(outputTask2 = taskBuffer.getTask());
    BOOST_CHECK_EQUAL(taskBuffer.empty(), true);
    BOOST_CHECK_EQUAL(taskBuffer.size(), 0);
    outputTask2();
    BOOST_CHECK_EQUAL(task2Calls, 1);
}
