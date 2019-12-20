#pragma once

namespace dataflow::channels::ignorePredicates {

struct IgnoreDefaults {

    template <typename ValueType>
    [[nodiscard]] bool operator()([[maybe_unused]] const ValueType& val) const;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreDefaults.hpp"
