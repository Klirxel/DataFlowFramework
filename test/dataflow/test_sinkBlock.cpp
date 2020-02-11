/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <vector>

#include <dataflow/blocks/SinkBlock.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    using ValueType = int;
    Channel<ValueType> input1;
    Channel<ValueType> input2;

    //Definition of addAndStoreBlock
    ExecutorSeq executor {};
    std::vector<ValueType> dataStorage;
    auto addAndStore = [&dataStorage](ValueType&& val1, ValueType&& val2) {
        dataStorage.emplace_back(val1 + val2);
    };

    SinkBlock addAndStoreBlock(ChannelBundle(input1, input2), addAndStore, executor);

    //Input data
    input1.push(1);
    input2.push(2);
    input1.push(2);
    input2.push(2);

    //Check output
    BOOST_CHECK_EQUAL(dataStorage.at(0), 3);
    BOOST_CHECK_EQUAL(dataStorage.at(1), 4);
}
