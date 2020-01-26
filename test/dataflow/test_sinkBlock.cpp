/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <vector>

#include <dataflow/blocks/SinkBlock.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

struct Adder {

    void operator()(int input1, int input2) noexcept { resultBuf.push_back(input1 + input2); }

    std::vector<int> resultBuf;
};

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Channel<int> input1;
    Channel<int> input2;
    Adder adder;

    ExecutorSeq executor {};

    SinkBlock sinkBlock(ChannelBundle(input1, input2), adder, executor);

    input1.push(1);
    input2.push(2);

    BOOST_CHECK_EQUAL(adder.resultBuf.at(0), 3);

    input1.push(2);
    input2.push(2);

    BOOST_CHECK_EQUAL(adder.resultBuf.at(1), 4);
}
