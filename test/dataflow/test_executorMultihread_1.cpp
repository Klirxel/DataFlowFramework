/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testExecutorMultihread_1
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <set>

#include <dataflow/blocks/Block.h>
#include <dataflow/blocks/GeneratorBlock.h>
#include <dataflow/blocks/SinkBlock.h>
#include <dataflow/channels/ChannelThreadSave.h>
#include <dataflow/executors/ExecutorMultithread.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    using ValueType = int;
    ChannelThreadSafe<ValueType> inputChan;
    ChannelThreadSafe<ValueType> chanRes;

    auto counter = [count = 0]() mutable {
        return count++;
    };
    GeneratorBlock inputGenerator { counter, ChannelBundle { inputChan } };

    const size_t threads = 9;
    ExecutorMultithread execMultihread { threads };

    const auto delayMultiply2 = 8ms;
    auto multiply2 = [&delayMultiply2](auto input) {
        std::this_thread::sleep_for(delayMultiply2);
        return 2 * input;
    };

    Block multiplyBlock1 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock2 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock3 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock4 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock5 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock6 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock7 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock8 { ChannelBundle { inputChan }, multiply2, ChannelBundle { chanRes }, execMultihread };

    auto dataStorage = std::vector<ValueType> {};
    auto storeData = [&dataStorage](ValueType&& data) {
        dataStorage.push_back(std::forward<ValueType>(data));
    };

    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, storeData, execMultihread };

    const auto starttime = std::chrono::system_clock::now();
    const size_t cycles = 1000;
    const auto period = 1ms;
    const auto offset = 0ms;
    inputGenerator.start(period, offset, cycles);
    inputGenerator.wait();
    execMultihread.stop();

    const auto stoptime = std::chrono::system_clock::now();
    const auto processingDuration = stoptime - starttime;

    std::cout << "ProcessingTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(processingDuration).count() << "ms \n";
    std::cout << "ProcessingTime (singleThread): " << cycles * delayMultiply2.count() << " ms \n";
    std::cout << "ProcessingTime (multiThread ideal): " << cycles * delayMultiply2.count() / threads << " ms \n";

    BOOST_CHECK_EQUAL(inputChan.dataAvailable(), false);

    std::set<size_t> resultsUnordered {};
    for (size_t cycle = 0; cycle < cycles; ++cycle) {
        resultsUnordered.insert(2 * cycle);
    }

    for (const auto& resultOfCycle : dataStorage) {
        BOOST_CHECK_EQUAL(resultsUnordered.count(resultOfCycle), 1);
        resultsUnordered.erase(resultOfCycle);
    }

    for (auto missedElem : resultsUnordered) {
        std::cout << "MissedElem" << missedElem << '\n';
    }

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
}
