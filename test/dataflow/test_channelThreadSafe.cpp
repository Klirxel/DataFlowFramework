/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testLockingChannel
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <vector>

#include <dataflow/blocks/Block.h>
#include <dataflow/blocks/GeneratorBlock.h>
#include <dataflow/blocks/SinkBlock.h>
#include <dataflow/channels/ChannelThreadSave.h>
#include <dataflow/executors/ExecutorAsync.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    using ValueType = int;

    ChannelThreadSafe<ValueType> chan1;
    ChannelThreadSafe<ValueType> chan2;
    ChannelThreadSafe<ValueType> chanRes;

    //Definiton of inputGenerators
    auto counter1 = [count = 0]() mutable { return count++; };
    auto counter2 = [count = 0]() mutable { return count++; };
    GeneratorBlock inputGenerator1 { counter1, ChannelBundle { chan1 } };
    GeneratorBlock inputGenerator2 { counter2, ChannelBundle { chan2 } };

    //Definition of addBlock
    ExecutorAsync execAsync1 { std::launch::async };
    auto adder = [](auto&& val1, auto&& val2) { return val1 + val2; };
    Block addBlock(ChannelBundle(chan1, chan2), adder, ChannelBundle(chanRes), execAsync1);

    //Defention of dataStorageBlock
    std::vector<ValueType> dataStorage;
    auto storeData = [&dataStorage](ValueType&& val) {
        dataStorage.emplace_back(std::forward<ValueType>(val));
    };

    ExecutorAsync execAsync2 { std::launch::async };
    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, storeData, execAsync2 };

    //Start generators
    const auto period = 10ms;
    const auto offset = 0ms;
    const auto elemToGen = 6;
    inputGenerator1.start(period, offset, elemToGen);
    inputGenerator2.start(period, offset, elemToGen);

    inputGenerator1.wait();
    inputGenerator2.wait();

    //Check result
    BOOST_CHECK_EQUAL(chan1.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan1.size(), 0);
    BOOST_CHECK_EQUAL(chan2.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan2.size(), 0);

    BOOST_CHECK_EQUAL(dataStorage.at(0), 0);
    BOOST_CHECK_EQUAL(dataStorage.at(1), 2);
    BOOST_CHECK_EQUAL(dataStorage.at(2), 4);
    BOOST_CHECK_EQUAL(dataStorage.at(3), 6);
    BOOST_CHECK_EQUAL(dataStorage.at(4), 8);
    BOOST_CHECK_EQUAL(dataStorage.at(5), 10);

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
}
