#define BOOST_TEST_MODULE testTransmissionAnalyser
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "TransmissionAnalyser.h"

using namespace dataflow::tools;

BOOST_AUTO_TEST_CASE(DefaultCtorCall)
{
    const TransmissionAnalyser ta {};

    BOOST_CHECK_EQUAL(ta.callsCopyCtor, 0);
    BOOST_CHECK_EQUAL(ta.callsMoveCtor, 0);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0);
    BOOST_CHECK_EQUAL(ta.callsMoveAssOp, 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 0);
}

BOOST_AUTO_TEST_CASE(CopyCtorCall)
{
    TransmissionAnalyser taBase {};
    const int offset = 10;
    taBase.calls.fill(offset);
    TransmissionAnalyser::callsDestructor = offset;

    const TransmissionAnalyser ta { taBase };

    BOOST_CHECK_EQUAL(ta.callsCopyCtor, 1 + offset);
    BOOST_CHECK_EQUAL(ta.callsMoveCtor, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsMoveAssOp, 0 + offset);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 0 + offset);
}

BOOST_AUTO_TEST_CASE(MoveCtorCall)
{
    TransmissionAnalyser taBase {};
    const int offset = 10;
    taBase.calls.fill(offset);
    TransmissionAnalyser::callsDestructor = offset;

    TransmissionAnalyser ta { std::move(taBase) };

    BOOST_CHECK_EQUAL(ta.callsCopyCtor, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsMoveCtor, 1 + offset);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsMoveAssOp, 0 + offset);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 0 + offset);
}

BOOST_AUTO_TEST_CASE(CopyAssOpCall)
{
    TransmissionAnalyser taBase {};
    const int offset = 10;
    taBase.calls.fill(offset);
    TransmissionAnalyser::callsDestructor = offset;

    TransmissionAnalyser ta {};
    ta = taBase;

    BOOST_CHECK_EQUAL(ta.callsCopyCtor, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsMoveCtor, 0 + offset);
    BOOST_CHECK_EQUAL(ta.callsCopyAssOp, 1 + offset);
    BOOST_CHECK_EQUAL(ta.callsMoveAssOp, 0 + offset);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 0 + offset);
}

BOOST_AUTO_TEST_CASE(DestructorCall)
{
    const int offset = 10;

    TransmissionAnalyser::callsDestructor = offset;

    {
        TransmissionAnalyser taBase {};
    }

    BOOST_CHECK_EQUAL(TransmissionAnalyser::callsDestructor, 1 + offset);
}
