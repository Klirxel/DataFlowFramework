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

class TwoChannelCounter {

public:
    constexpr std::tuple<size_t, size_t> operator()() noexcept
    {
        ++count_;
        return { count_, count_ };
    };

private:
    size_t count_ { 0 };
};

BOOST_AUTO_TEST_CASE(OutputPredicate)
{
    Channel<size_t> outputEven;
    Channel<size_t> outputOdd;

    auto outputChan1EvenChan2Odd = [](const size_t& chan1, const size_t& chan2) {
        return std::array<bool, 2> { chan1 % 2 == 0, chan2 % 2 == 1 };
    };

    TwoChannelCounter counter;

    GeneratorBlock genBlock(counter, ChannelBundle(outputEven, outputOdd), outputChan1EvenChan2Odd);

    const auto period = 1ms;
    const auto offset = 0ms;
    const size_t count = 6;

    genBlock.start(period, offset, count);
    std::this_thread::sleep_for(10ms);
    genBlock.stop();

    BOOST_CHECK_EQUAL(outputEven.size(), 3);
    BOOST_CHECK_EQUAL(outputOdd.size(), 3);
    BOOST_CHECK_EQUAL(outputOdd.pop().value(), 1);
    BOOST_CHECK_EQUAL(outputEven.pop().value(), 2);
    BOOST_CHECK_EQUAL(outputOdd.pop().value(), 3);
    BOOST_CHECK_EQUAL(outputEven.pop().value(), 4);
    BOOST_CHECK_EQUAL(outputOdd.pop().value(), 5);
    BOOST_CHECK_EQUAL(outputEven.pop().value(), 6);

    BOOST_CHECK(not outputEven.dataAvailable());
    BOOST_CHECK(not outputOdd.dataAvailable());
}
