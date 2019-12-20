#include "../ignorePredicates/IgnoreDefaults.h"

namespace dataflow::channels::ignorePredicates {

template <typename ValueType,
    typename = std::enable_if_t<std::is_default_constructible_v<ValueType>>,
    typename = std::enable_if_t<tools::is_compareable_v<ValueType, ValueType>>>
[[nodiscard]] bool IgnoreDefaults::operator()(const ValueType& val) const
{
    return val == ValueType {};
}

} // namespace dataflow::channels::ignorePredicates
