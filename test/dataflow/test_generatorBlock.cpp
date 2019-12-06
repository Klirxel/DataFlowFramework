#define BOOST_TEST_MODULE testGeneratorBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <dataflow/blocks/GeneratorBlock.h>
#include <dataflow/channels/Channel.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;

constexpr int kernel() noexcept
{
    return 1;
}

BOOST_AUTO_TEST_CASE(GenerateWait)
{
    Channel<int> output;

    GeneratorBlock genBlock(kernel, ChannelBundle(output));

    const auto period = 100ms;
    const auto offset = 0ms;
    const size_t count = 3;

    genBlock.start(period, offset, count);
    genBlock.wait();

    BOOST_CHECK_EQUAL(output.pop().value(), 1);
    BOOST_CHECK_EQUAL(output.pop().value(), 1);
    BOOST_CHECK_EQUAL(output.pop().value(), 1);
    BOOST_CHECK(not output.dataAvailable());
}

BOOST_AUTO_TEST_CASE(GenerateStop)
{
    Channel<int> output;

    GeneratorBlock genBlock(kernel, ChannelBundle(output));

    const auto period = 100ms;
    const auto offset = 0ms;
    const size_t count = inf;

    genBlock.start(period, offset, count);
    std::this_thread::sleep_for(450ms);
    genBlock.stop();

    BOOST_CHECK_EQUAL(output.pop().value(), kernel());
    BOOST_CHECK_EQUAL(output.pop().value(), kernel());
    BOOST_CHECK_EQUAL(output.pop().value(), kernel());
    BOOST_CHECK_EQUAL(output.pop().value(), kernel());
    BOOST_CHECK_EQUAL(output.pop().value(), kernel());
    BOOST_CHECK(not output.dataAvailable());
}