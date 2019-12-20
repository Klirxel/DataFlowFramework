#pragma once

namespace dataflow::channels::ignorePredicates {

struct IgnoreNothing {

    template <typename ValueType>
    [[nodiscard]] constexpr bool operator()([[maybe_unused]] const ValueType& val) const noexcept;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreNothing.hpp"
