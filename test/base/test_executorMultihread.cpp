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

    ChannelThreadSafe<int> chan1, chan2;
    ChannelThreadSafe<int> chanRes;

    GeneratorBlock inputGenerator1 { counter1, ChannelBundle { chan1 } };
    GeneratorBlock inputGenerator2 { counter2, ChannelBundle { chan2 } };

    const size_t threads = 2;
    ExecutorMultithread execMultihread { threads };

    Block block { ChannelBundle { chan1, chan2 }, add, ChannelBundle { chanRes }, execMultihread };
    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, dataStorage, execMultihread };

    const size_t cycles = 1000;
    const auto period = 1ms;
    const auto offset = 0ms;
    inputGenerator1.start(period, offset, cycles);
    inputGenerator2.start(period, offset, cycles);

    inputGenerator1.wait();
    inputGenerator2.wait();

    BOOST_CHECK_EQUAL(chan1.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan2.dataAvailable(), false);

    for (size_t cycle = 0; cycle < cycles; ++cycle) {
        BOOST_CHECK_EQUAL(dataStorage.data.at(cycle), 2 * cycle);
    }

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);

    execMultihread.stop();
}
