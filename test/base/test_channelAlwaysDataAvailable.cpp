#define BOOST_TEST_MODULE testLockingChannel

#include <vector>

#include <boost/test/included/unit_test.hpp>

#include "Block.h"
#include "Channels.h"
#include "ExecutorAsync.h"

using namespace df::base;

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

    ExecutorAsync executor {};
    Block addBlock(ChannelBundle(chanAd, chan), operatorAdd, ChannelBundle(chanRes), executor);

    //No data
    BOOST_CHECK_EQUAL(chanAd.dataAvailable(), true);
    BOOST_CHECK_EQUAL(chanAd.pop(), 0);

    //Insert data (default construction on chanDa);
    chan.push(2);
    BOOST_CHECK_EQUAL(chanRes.pop(), 2);

    //Insert data (no default construction if data is available)
    chanAd.push(3);
    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
    chan.push(3);
    BOOST_CHECK_EQUAL(chanRes.pop(), 6);
}

BOOST_AUTO_TEST_CASE(Test_channelAdTs)
{
    ChannelAdTs<int> chanAdTs;
    Channel<int> chan;
    Channel<int> chanRes;

    ExecutorAsync executor {};
    Block addBlock(ChannelBundle(chanAdTs, chan), operatorAdd, ChannelBundle(chanRes), executor);

    //No data
    BOOST_CHECK_EQUAL(chanAdTs.dataAvailable(), true);
    BOOST_CHECK_EQUAL(chanAdTs.pop(), 0);

    //Insert data (default construction on chanDa);
    chan.push(2);
    BOOST_CHECK_EQUAL(chanRes.pop(), 2);

    //Insert data (no default construction if data is available)
    chanAdTs.push(3);
    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
    chan.push(3);
    BOOST_CHECK_EQUAL(chanRes.pop(), 6);
}
