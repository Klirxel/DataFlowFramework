/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testChannelBundle
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/channels/Channel.h>
#include <dataflow/channels/ChannelBundle.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;

BOOST_AUTO_TEST_CASE(Test_size)
{
    Channel<int> chan1;
    Channel<int> chan2;

    //Description<chan>: size of chan
    //chan1: 0, chan2: 0
    ChannelBundle chanBundle { chan1, chan2 };
    BOOST_CHECK_EQUAL(chanBundle.size(), 0);

    //chan1: 1, chan2: 0
    chan1.push(0);
    BOOST_CHECK_EQUAL(chanBundle.size(), 0);

    //chan1: 1, chan2: 1
    chan2.push(0);
    BOOST_CHECK_EQUAL(chanBundle.size(), 1);

    //chan1: 1, chan2: 2
    chan2.push(0);
    BOOST_CHECK_EQUAL(chanBundle.size(), 1);

    //chan1: 2, chan2: 2
    chan1.push(0);
    BOOST_CHECK_EQUAL(chanBundle.size(), 2);
}

BOOST_AUTO_TEST_CASE(Test_max_size)
{
    Channel<int> chan1;
    Channel<int> chan2;

    ChannelBundle chanBundle { chan1, chan2 };

    BOOST_CHECK_EQUAL(chan1.max_size(), std::numeric_limits<size_t>::max());
    BOOST_CHECK_EQUAL(chan2.max_size(), std::numeric_limits<size_t>::max());
    BOOST_CHECK_EQUAL(chanBundle.max_size(), std::numeric_limits<size_t>::max());
}
