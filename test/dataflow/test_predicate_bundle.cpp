/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/tools/old/interface.hpp>
#define BOOST_TEST_MODULE testPredicateBundle
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/blocks/PredicateBundle.h>

using namespace dataflow::blocks;

constexpr bool is_zero(int val) { return val == 0; }
constexpr bool is_not_zero(int val) { return val != 0; }

BOOST_AUTO_TEST_CASE(testPredicateBundle)
{
    /********************************************************************************
     * Setup test environment
     ********************************************************************************/
    auto vec_of_size_two = [](const std::vector<int>& vec) { return vec.size() == 2; };

    PredicateBundle predicateBundle {
        is_zero,
        is_not_zero,
        vec_of_size_two
    };

    const auto vec_0 = std::vector<int> {};
    const auto vec_2 = std::vector<int> { 1, 2 };

    /********************************************************************************
     * Test case 
     ********************************************************************************/
    BOOST_CHECK((predicateBundle(0, 1, vec_0) == std::array<bool, 3> { true, true, false }));
    BOOST_CHECK((predicateBundle(1, 0, vec_2) == std::array<bool, 3> { false, false, true }));
    BOOST_CHECK((predicateBundle(0, 0, vec_0) == std::array<bool, 3> { true, false, false }));
    BOOST_CHECK((predicateBundle(1, 1, vec_2) == std::array<bool, 3> { false, true, true }));
}
