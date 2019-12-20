#pragma once

namespace dataflow::channels::ignorePredicates {

template <typename ValueType>
struct IgnoreNothing {

    [[nodiscard]] constexpr bool operator()([[maybe_unused]] const ValueType& val) const noexcept;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreNothing.hpp"
