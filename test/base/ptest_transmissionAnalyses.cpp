#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Block.h"
#include "Channel.h"
#include "Executor.h"
#include "TransmissionAnalyser.h"

using namespace df::base;

inline TransmissionAnalyser moveThrough(TransmissionAnalyser&& ta) noexcept { return std::move(ta); }

BOOST_AUTO_TEST_CASE(AnalyseDataMoveCount)
{
    Channel<TransmissionAnalyser> inputChan;
    Channel<TransmissionAnalyser> outputChan;

    Executor executor {};

    Block block { ChannelBundle { inputChan }, moveThrough, ChannelBundle { outputChan }, executor };

    inputChan.push(TransmissionAnalyser {});

    const TransmissionAnalyser ta = outputChan.pop();

    BOOST_CHECK_EQUAL(ta.callsCopyCtor, 0);
    BOOST_CHECK_EQUAL(ta.callsMoveCtor, 7);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0);
    BOOST_CHECK_EQUAL(ta.callsMoveAssOp, 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 7);
}

inline TransmissionAnalyser copyThrough(const TransmissionAnalyser& ta) noexcept { return ta; }

BOOST_AUTO_TEST_CASE(AnalyseDataCopyCount)
{
    Channel<TransmissionAnalyser> inputChan;
    Channel<TransmissionAnalyser> outputChan;

    Executor executor {};

    Block block { ChannelBundle { inputChan }, copyThrough, ChannelBundle { outputChan }, executor };

    inputChan.push(TransmissionAnalyser {});

    const TransmissionAnalyser ta = outputChan.pop();

    BOOST_CHECK_EQUAL(ta.callsCopyCtor, 1);
    BOOST_CHECK_EQUAL(ta.callsMoveCtor, 6);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0);
    BOOST_CHECK_EQUAL(ta.callsMoveAssOp, 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 15);
}
