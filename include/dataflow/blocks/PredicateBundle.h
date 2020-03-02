/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <array>

namespace dataflow::blocks {

/**
 * @brief Bundle of predicates
 *
 * @details
 * - Combinig one-input predicates to a multi-input predicate.
 * - Used for creating an outputPredicate
 *   for dataflow::blocks
 *   with multiple output-channels by combing the
 *   outputPredicates for each of the ouput-channels.
 *
 */
template <typename... Predicates>
class PredicateBundle {
public:
    constexpr PredicateBundle(const Predicates&... predicates) noexcept;

    template <typename... PredicateInput>
    std::array<bool, sizeof...(Predicates)>
    operator()(const PredicateInput&... predicateInput) const;

private:
    template <typename... PredicateInput, size_t... Is>
    std::array<bool, sizeof...(Predicates)>
    eval(std::index_sequence<Is...>, const PredicateInput&... predicateInput) const;

private:
    std::tuple<const Predicates&...> predicates_;
};

} // namespace dataflow::blocks

#include "impl/PredicateBundle.hpp"
