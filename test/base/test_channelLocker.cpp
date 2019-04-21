#define BOOST_TEST_MODULE testLockingChannel

#include <vector>

#include <boost/test/included/unit_test.hpp>

#include "Block.h"
#include "Channel.h"
#include "ChannelLocker.h"
#include "GeneratorBlock.h"
#include "SinkBlock.h"

#include "ExecutorAsync.h"

using namespace df::base;

struct Counter {

    constexpr int operator()() noexcept
    {
        return count++;
    };

    int count { 0 };
};

struct DataStorage {

    void operator()(int value)
    {
        data.push_back(value);
    };

    std::vector<int> data;
};

constexpr int
add(int input1, int input2) noexcept
{
    return input1 + input2;
}

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Counter counter1, counter2;
    DataStorage dataStorage;

    Channel<int> chan1, chan2;
    Channel<int> result;

    ChannelLocker chan1Locked { chan1 };
    ChannelLocker chan2Locked { chan2 };
    ChannelLocker resultLocked { result };

    GeneratorBlock inputGenerator1 { counter1, ChannelBundle { chan1Locked } };
    GeneratorBlock inputGenerator2 { counter2, ChannelBundle { chan2Locked } };

    ExecutorAsync execAsync1 { std::launch::async };
    Block block(ChannelBundle(chan1Locked, chan2Locked), add, ChannelBundle(resultLocked), execAsync1);

    ExecutorAsync execAsync2 { std::launch::async };
    SinkBlock dataStorageBlock { ChannelBundle { resultLocked }, dataStorage, execAsync2 };

    inputGenerator1.start(10ms, 0ms, 6);
    inputGenerator2.start(10ms, 0ms, 6);

    inputGenerator1.wait();
    inputGenerator2.wait();

    BOOST_CHECK_EQUAL(chan1Locked.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan2Locked.dataAvailable(), false);

    BOOST_CHECK_EQUAL(dataStorage.data.at(0), 0);
    BOOST_CHECK_EQUAL(dataStorage.data.at(1), 2);
    BOOST_CHECK_EQUAL(dataStorage.data.at(2), 4);
    BOOST_CHECK_EQUAL(dataStorage.data.at(3), 6);
    BOOST_CHECK_EQUAL(dataStorage.data.at(4), 8);
    BOOST_CHECK_EQUAL(dataStorage.data.at(5), 10);

    BOOST_CHECK_EQUAL(resultLocked.dataAvailable(), false);
}
