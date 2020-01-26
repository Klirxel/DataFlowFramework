/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testExecutorMultihread_2
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <set>

#include <dataflow/blocks/Block.h>
#include <dataflow/blocks/GeneratorBlock.h>
#include <dataflow/blocks/SinkBlock.h>
#include <dataflow/channels/channels.h>
#include <dataflow/executors/ExecutorMultithread.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

struct Counter {

    int operator()() noexcept
    {
        return count++;
    };

    int count { 0 };
};

int multiply(int a, int b) noexcept
{
    return a * b;
}

std::tuple<int, int> doubler(int a) noexcept
{
    return { a, a };
}

struct DataStorage {

    void operator()(int value)
    {
        data.push_back(value);
    };

    std::vector<int> data;
};

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Counter counter1;
    Counter counter2;
    DataStorage dataStorage1;
    DataStorage dataStorage2;

    ChannelThreadSafe<int> chanIn1, chanIn2;
    ChannelThreadSafe<int> chan11, chan12;
    ChannelThreadSafe<int> chan21, chan22;
    ChannelThreadSafe<int> chanOut1, chanOut2;

    GeneratorBlock inputGenerator1 { counter1, ChannelBundle { chanIn1 } };
    GeneratorBlock inputGenerator2 { counter2, ChannelBundle { chanIn2 } };

    const size_t threads = 4;
    ExecutorMultithread execMultihread { threads };

    Block doublerBlock1 { ChannelBundle { chanIn1 }, doubler, ChannelBundle { chan11, chan12 }, execMultihread };
    Block doublerBlock2 { ChannelBundle { chanIn2 }, doubler, ChannelBundle { chan21, chan22 }, execMultihread };

    Block multiplyBlock1 { ChannelBundle { chan11, chan21 }, multiply, ChannelBundle { chanOut1 }, execMultihread };
    Block multiplyBlock2 { ChannelBundle { chan12, chan22 }, multiply, ChannelBundle { chanOut2 }, execMultihread };

    SinkBlock dataStorageBlock1 { ChannelBundle { chanOut1 }, dataStorage1, execMultihread };
    SinkBlock dataStorageBlock2 { ChannelBundle { chanOut2 }, dataStorage2, execMultihread };

    const auto starttime = std::chrono::system_clock::now();

    const size_t cycles = 1000;
    const auto period = 1ms;
    const auto offset1 = 0ms;
    const auto offset2 = 0ms;
    inputGenerator1.start(period, offset1, cycles);
    inputGenerator2.start(period, offset2, cycles);
    inputGenerator1.wait();
    inputGenerator2.wait();
    std::this_thread::sleep_for(10ms); //give him some time to process the last elements.
    execMultihread.stop();

    const auto stoptime = std::chrono::system_clock::now();
    const auto processingDuration = stoptime - starttime;

    std::cout << "ProcessingTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(processingDuration).count() << "ms \n";
    std::cout << "IdealProcessingTime around: " << cycles << "ms \n";

    BOOST_CHECK_EQUAL(chanIn1.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chanIn2.dataAvailable(), false);
    BOOST_CHECK_EQUAL(dataStorage1.data.size(), cycles);
    BOOST_CHECK_EQUAL(dataStorage2.data.size(), cycles);

    const size_t elemsBoth = std::min(dataStorage1.data.size(), dataStorage2.data.size());
    for (size_t cycle = 0; cycle < elemsBoth; ++cycle) {
        BOOST_CHECK_EQUAL(dataStorage1.data.at(cycle), dataStorage2.data.at(cycle));
    }
}
