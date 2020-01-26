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

    ChannelThreadSafe<int> chan1, chan2;
    ChannelThreadSafe<int> chanRes;

    GeneratorBlock inputGenerator1 { counter1, ChannelBundle { chan1 } };
    GeneratorBlock inputGenerator2 { counter2, ChannelBundle { chan2 } };

    ExecutorAsync execAsync1 { std::launch::async };
    Block block(ChannelBundle(chan1, chan2), add, ChannelBundle(chanRes), execAsync1);

    ExecutorAsync execAsync2 { std::launch::async };
    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, dataStorage, execAsync2 };

    inputGenerator1.start(10ms, 0ms, 6);
    inputGenerator2.start(10ms, 0ms, 6);

    inputGenerator1.wait();
    inputGenerator2.wait();

    BOOST_CHECK_EQUAL(chan1.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan1.size(), 0);
    BOOST_CHECK_EQUAL(chan2.dataAvailable(), false);
    BOOST_CHECK_EQUAL(chan2.size(), 0);

    BOOST_CHECK_EQUAL(dataStorage.data.at(0), 0);
    BOOST_CHECK_EQUAL(dataStorage.data.at(1), 2);
    BOOST_CHECK_EQUAL(dataStorage.data.at(2), 4);
    BOOST_CHECK_EQUAL(dataStorage.data.at(3), 6);
    BOOST_CHECK_EQUAL(dataStorage.data.at(4), 8);
    BOOST_CHECK_EQUAL(dataStorage.data.at(5), 10);

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
}
