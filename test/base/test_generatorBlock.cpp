#define BOOST_TEST_MODULE testGeneratorBlock

#include <iostream>

#include <boost/test/included/unit_test.hpp>

#include "Channel.h"
#include "GeneratorBlock.h"

using namespace df::base;

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

    BOOST_CHECK_EQUAL(output.pop(), 1);
    BOOST_CHECK_EQUAL(output.pop(), 1);
    BOOST_CHECK_EQUAL(output.pop(), 1);
    BOOST_CHECK(output.empty());
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

    BOOST_CHECK_EQUAL(output.size(), 5);
}
