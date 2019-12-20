#include "../ignorePredicates/IgnoreDefaults.h"

namespace dataflow::channels::ignorePredicates {

template <typename ValueType>
[[nodiscard]] bool IgnoreDefaults<ValueType>::operator()(const ValueType& val) const
{
    return val == ValueType {};
}

} // namespace dataflow::channels::ignorePredicates
