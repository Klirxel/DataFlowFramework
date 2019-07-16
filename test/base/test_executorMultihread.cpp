#define BOOST_TEST_MODULE testExecutorMultihread
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Block.h"
#include "Channels.h"
#include "ExecutorMultithread.h"
#include "GeneratorBlock.h"
#include "SinkBlock.h"

using namespace df::base;

struct Counter {

    int operator()() noexcept
    {
        std::lock_guard<std::mutex> lock { mutex };
        return count++;
    };

    int count { 0 };
    std::mutex mutex;
};

struct DataStorage {

    void operator()(int value)
    {
        std::lock_guard<std::mutex> lock { mutex };
        data.push_back(value);
    };

    std::vector<int> data;
    std::mutex mutex;
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

    ChannelThreadSafe<int> chan1, chan2;
    ChannelThreadSafe<int> chanRes;

    GeneratorBlock inputGenerator1 { counter1, ChannelBundle { chan1 } };
    GeneratorBlock inputGenerator2 { counter2, ChannelBundle { chan2 } };

    const size_t threads = 2;
    ExecutorMultithread execMultihread { threads };

    Block block { ChannelBundle { chan1, chan2 }, add, ChannelBundle { chanRes }, execMultihread };
    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, dataStorage, execMultihread };

    inputGenerator1.start(10ms, 0ms, 6);
    inputGenerator2.start(10ms, 0ms, 6);

    inputGenerator1.wait();
    inputGenerator2.wait();

    BOOST_CHECK_EQUAL(chan1.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan2.dataAvailable(), false);

    BOOST_CHECK_EQUAL(dataStorage.data.at(0), 0);
    BOOST_CHECK_EQUAL(dataStorage.data.at(1), 2);
    BOOST_CHECK_EQUAL(dataStorage.data.at(2), 4);
    BOOST_CHECK_EQUAL(dataStorage.data.at(3), 6);
    BOOST_CHECK_EQUAL(dataStorage.data.at(4), 8);
    BOOST_CHECK_EQUAL(dataStorage.data.at(5), 10);

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);

    execMultihread.stop();
}
