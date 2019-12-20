#pragma once

#include "../../tools/is_compareable.h"

namespace dataflow::channels::ignorePredicates {

struct IgnoreDefaults {

    template <typename ValueType,
        typename = std::enable_if_t<std::is_default_constructible_v<ValueType>>,
        typename = std::enable_if_t<tools::is_compareable_v<ValueType, ValueType>>>
    [[nodiscard]] bool operator()([[maybe_unused]] const ValueType& val) const;
};

} // namespace dataflow::channels::ignorePredicates

#include "../impl/IgnoreDefaults.hpp"
