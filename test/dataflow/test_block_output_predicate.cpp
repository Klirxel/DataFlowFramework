/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE test_block_output_predicate
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/blocks/Block.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

BOOST_AUTO_TEST_CASE(BasicOutputPredicate)
{
    using ValueType = int;
    Channel<ValueType> chanIn;
    Channel<ValueType> chanOut;

    ExecutorSeq executor;

    //Definition passThroughOnlyEvenBlock
    auto passThrough = [](ValueType&& val) { return std::forward<ValueType>(val); };

    auto outputOnlyEven = [](const auto&... inputPack) {
        auto isEven = [](const auto& number) { return number % 2 == 0; };
        return std::array { isEven(inputPack)... };
    };

    Block passThroughOnlyEven { ChannelBundle { chanIn },
        passThrough, ChannelBundle { chanOut }, executor, outputOnlyEven };

    //Test run
    const size_t cycles = 101;

    for (size_t cycle = 0; cycle < cycles; ++cycle) {
        chanIn.push(cycle);
    };

    //Test evaluation
    const size_t cyclesEven = cycles % 2 == 0 ? cycles / 2 : cycles / 2 + 1;

    BOOST_CHECK_EQUAL(chanOut.size(), cyclesEven);

    for (size_t i = 0; i < cyclesEven; ++i) {
        BOOST_CHECK_EQUAL(chanOut.pop().value() % 2, 0);
    }
}
