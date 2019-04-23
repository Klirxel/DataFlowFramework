#define BOOST_TEST_MODULE testBaseBlock

#include <iostream>

#include <boost/test/included/unit_test.hpp>

#include "Block.h"
#include "Channel.h"
#include "ExecutorAsync.h"

using namespace df::base;

constexpr int add(int input1, int input2) noexcept { return input1 + input2; }

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Channel<int> input1;
    Channel<int> input2;
    Channel<int> result;

    ExecutorAsync execAsync {};

    Block block(ChannelBundle(input1, input2), add, ChannelBundle(result), execAsync);

    input1.push(1);
    input2.push(2);

    execAsync.wait();

    BOOST_CHECK_EQUAL(result.pop(), 3);
}
