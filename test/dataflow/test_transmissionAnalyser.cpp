/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testTransmissionAnalyser
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/tools/TransmissionAnalyser.h>

using namespace dataflow::tools;

BOOST_AUTO_TEST_CASE(DefaultCtorCall)
{
    const TransmissionAnalyser ta {};

    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 0);
}

BOOST_AUTO_TEST_CASE(CopyCtorCall)
{

    //from last test
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 1);

    TransmissionAnalyser taBase {};
    const TransmissionAnalyser ta { taBase };

    BOOST_CHECK_EQUAL(taBase.getCallsCopyCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 1);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getAndResetCallsDestructor(), 0);
}

BOOST_AUTO_TEST_CASE(MoveCtorCall)
{
    //from last test
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 2);

    TransmissionAnalyser taBase {};

    TransmissionAnalyser ta { std::move(taBase) };

    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 1);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 0);
}

BOOST_AUTO_TEST_CASE(CopyAssOpCall)
{
    //from last test
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 2);

    TransmissionAnalyser taBase {};

    TransmissionAnalyser ta {};
    ta = taBase;

    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 1);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 0);
}

BOOST_AUTO_TEST_CASE(CopyAssOpCallSelfAssingProtection)
{
    //from last test
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 2);

    TransmissionAnalyser ta {};
    ta = *&ta;

    BOOST_CHECK_EQUAL(ta.getCallsCopyCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveCtor(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsCopyAssOp(), 0);
    BOOST_CHECK_EQUAL(ta.getCallsMoveAssOp(), 0);
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 0);
}

BOOST_AUTO_TEST_CASE(DestructorCall)
{
    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 1);

    {
        TransmissionAnalyser taBase {};
    }

    BOOST_CHECK_EQUAL(TransmissionAnalyser::getAndResetCallsDestructor(), 1);
}
