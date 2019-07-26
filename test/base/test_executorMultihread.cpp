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
        std::cout << "Counter: Input data " << count << std::endl;
        return count++;
    };

    int count { 0 };
};

template <size_t index>
int multiply2(int input) noexcept
{
    std::cout << "multiply2Unit-" << index << ": 2 * " << input << std::endl;
    std::this_thread::sleep_for(1s);
    return 2 * input;
}

struct DataStorage {

    void operator()(int value)
    {
        std::cout << "DataStorage: Receive data: " << value << std::endl;
        data.push_back(value);
    };

    std::vector<int> data;
};

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Counter counter;
    DataStorage dataStorage;

    ChannelThreadSafe<int> inputChan;
    ChannelThreadSafe<int> chanRes;

    GeneratorBlock inputGenerator { counter, ChannelBundle { inputChan } };

    const size_t threads = 1;
    ExecutorMultithread execMultihread { threads };

    Block multiplyBlock1 { ChannelBundle { inputChan }, multiply2<1>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock2 { ChannelBundle { inputChan }, multiply2<2>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock3 { ChannelBundle { inputChan }, multiply2<3>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock4 { ChannelBundle { inputChan }, multiply2<4>, ChannelBundle { chanRes }, execMultihread };
    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, dataStorage, execMultihread };

    const size_t cycles = 10;
    const auto period = 500ms;
    const auto offset = 0ms;
    inputGenerator.start(period, offset, cycles);

    inputGenerator.wait();
    execMultihread.stop();

    BOOST_CHECK_EQUAL(inputChan.dataAvailable(), false);

    for (size_t cycle = 0; cycle < cycles; ++cycle) {
        BOOST_CHECK_EQUAL(dataStorage.data.at(cycle), 2 * cycle);
    }

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
}
