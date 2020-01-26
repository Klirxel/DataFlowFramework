/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#define BOOST_TEST_MODULE testIsCompareable
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/tools/is_compareable.h>

using namespace dataflow;

BOOST_AUTO_TEST_CASE(IsCompareable_valid)
{
    bool isCompareable;

    isCompareable = tools::is_compareable_v<int, int>;
    BOOST_CHECK(isCompareable);

    isCompareable = tools::is_compareable_v<float, int>;
    BOOST_CHECK(isCompareable);

    isCompareable = tools::is_compareable_v<std::nullptr_t, void*>;
    BOOST_CHECK(isCompareable);
}

BOOST_AUTO_TEST_CASE(IsCompareable_invalid)
{
    bool isCompareable;

    isCompareable = tools::is_compareable_v<std::nullptr_t, float>;
    BOOST_CHECK(not isCompareable);
    
    isCompareable = tools::is_compareable_v<int*, float*>;
    BOOST_CHECK(not isCompareable);
}
