/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/blocks/Block.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>
#include <dataflow/tools/TransmissionAnalyser.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;
using namespace dataflow::tools;

inline TransmissionAnalyser moveThrough(TransmissionAnalyser&& ta) noexcept { return std::move(ta); }

BOOST_AUTO_TEST_CASE(AnalyseDataMoveCount)
{
    Channel<TransmissionAnalyser> inputChan;
    Channel<TransmissionAnalyser> outputChan;

    ExecutorSeq executor {};

    Block block { ChannelBundle { inputChan }, moveThrough, ChannelBundle { outputChan }, executor };

    inputChan.push(TransmissionAnalyser {});

    const TransmissionAnalyser ta = outputChan.pop().value();

    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 9);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 9);
}

inline TransmissionAnalyser copyThrough(const TransmissionAnalyser& ta) noexcept { return ta; }

BOOST_AUTO_TEST_CASE(AnalyseDataCopyCount)
{
    Channel<TransmissionAnalyser> inputChan;
    Channel<TransmissionAnalyser> outputChan;

    ExecutorSeq executor {};

    Block block { ChannelBundle { inputChan }, copyThrough, ChannelBundle { outputChan }, executor };

    inputChan.push(TransmissionAnalyser {});

    const TransmissionAnalyser ta = outputChan.pop().value();

    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 1);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 8);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 19);
}
