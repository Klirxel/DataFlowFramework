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
 * @brief Generic output predicate for blocks. 
 *
 * @details
 * - Can be uesed to create an output predicate for an block by
 *   by specifying the output predicates for each output channel.
 * - Technical:
 *   OutPredChan1: T1 -> bool, OutPredChan2: T2 -> bool ... => 
 *   OutputPredicate(OutPredChan1,PredChan2,...): T1,T2,... -> std::array<bool,sizeof(Preds)>
 *
 */
template <typename... Predicates>
class OutputPredicate {
public:
    constexpr OutputPredicate(const Predicates&... predicates) noexcept;

    template <typename... PredicateInput>
    std::array<bool, sizeof...(Predicates)>
    operator()(const PredicateInput&... predicateInput) const;

private:
    template <typename... PredicateInput, size_t... Is>
    [[nodiscard]] std::array<bool, sizeof...(Predicates)>
    evalPredicates(std::index_sequence<Is...> /*unused*/,
        const PredicateInput&... predicateInput) const;

private:
    std::tuple<const Predicates&...> predicates_;
};

} // namespace dataflow::blocks

#include "impl/OutputPredicate.hpp"
