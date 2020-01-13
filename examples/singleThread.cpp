#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <dataflow/blocks/Block.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

constexpr int add(int input1, int input2) noexcept { return input1 + input2; }

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Channel<int> input1;
    Channel<int> input2;
    Channel<int> result;

    ExecutorSeq executor {};

    Block block(ChannelBundle(input1, input2), add, ChannelBundle(result), executor);

    input1.push(1);
    input2.push(2);

    BOOST_CHECK_EQUAL(result.dataAvailable(), true);
    BOOST_CHECK_EQUAL(result.size(), 1);
    BOOST_CHECK_EQUAL(result.pop().value(), 3);
}
