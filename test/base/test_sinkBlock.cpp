#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <vector>

#include "Channel.h"
#include "Executor.h"
#include "SinkBlock.h"

using namespace df::base;

struct Adder {

    void operator()(int input1, int input2) noexcept { resultBuf.push_back(input1 + input2); }

    std::vector<int> resultBuf;
};

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Channel<int> input1;
    Channel<int> input2;
    Adder adder;

    Executor executor {};

    SinkBlock sinkBlock(ChannelBundle(input1, input2), adder, executor);

    input1.push(1);
    input2.push(2);

    BOOST_CHECK_EQUAL(adder.resultBuf.at(0), 3);

    input1.push(2);
    input2.push(2);

    BOOST_CHECK_EQUAL(adder.resultBuf.at(1), 4);
}
