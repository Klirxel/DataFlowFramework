#define BOOST_TEST_MODULE testLockingChannel
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <vector>

#include "blocks/Block.h"
#include "channels/Channels.h"
#include "executors/Executor.h"

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

constexpr int
operatorAdd(int input1, int input2) noexcept
{
    return input1 + input2;
}

BOOST_AUTO_TEST_CASE(Test_channelAlwaysDataAvailable)
{
    ChannelAlwaysDataAvailable<int> chanAd;
    Channel<int> chan;
    Channel<int> chanRes;

    Executor executor {};
    Block addBlock(ChannelBundle(chanAd, chan), operatorAdd, ChannelBundle(chanRes), executor);

    //No data
    BOOST_CHECK_EQUAL(chanAd.dataAvailable(), true);
    BOOST_CHECK_EQUAL(chanAd.size(), std::numeric_limits<size_t>::max());
    BOOST_CHECK_EQUAL(chanAd.pop().value(), 0);

    //Insert data (default construction on chanDa);
    chan.push(2);
    BOOST_CHECK_EQUAL(chanRes.pop().value(), 2);

    //Insert data (no default construction if data is available)
    chanAd.push(3);
    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
    chan.push(3);
    BOOST_CHECK_EQUAL(chanRes.pop().value(), 6);
}

BOOST_AUTO_TEST_CASE(Test_channelAdTs)
{
    ChannelAdTs<int> chanAdTs;
    Channel<int> chan;
    Channel<int> chanRes;

    Executor executor {};
    Block addBlock(ChannelBundle(chanAdTs, chan), operatorAdd, ChannelBundle(chanRes), executor);

    //No data
    BOOST_CHECK_EQUAL(chanAdTs.dataAvailable(), true);
    BOOST_CHECK_EQUAL(chanAdTs.pop().value(), 0);

    //Insert data (default construction on chanDa);
    chan.push(2);
    BOOST_CHECK_EQUAL(chanRes.pop().value(), 2);

    //Insert data (no default construction if data is available)
    chanAdTs.push(3);
    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);

    chan.push(3);
    BOOST_CHECK_EQUAL(chanRes.pop().value(), 6);
}
