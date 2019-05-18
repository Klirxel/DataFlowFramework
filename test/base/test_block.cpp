#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>

#include "Block.h"
#include "Channel.h"
#include "Executor.h"

using namespace df::base;

constexpr int add(int input1, int input2) noexcept { return input1 + input2; }

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Channel<int> input1;
    Channel<int> input2;
    Channel<int> result;

    Executor executor {};

    Block block(ChannelBundle(input1, input2), add, ChannelBundle(result), executor);

    input1.push(1);
    input2.push(2);

    BOOST_CHECK_EQUAL(result.pop(), 3);
}
