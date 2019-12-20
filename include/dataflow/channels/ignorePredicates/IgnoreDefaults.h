#pragma once

namespace dataflow::channels::ignorePredicates {

template <typename ValueType>
struct IgnoreDefaults {

    [[nodiscard]] bool operator()([[maybe_unused]] const ValueType& val) const;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreDefaults.hpp"
