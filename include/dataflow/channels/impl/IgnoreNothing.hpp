#include "../ignorePredicates/IgnoreNothing.h"

namespace dataflow::channels::ignorePredicates {

template <typename ValueType>
[[nodiscard]] constexpr bool IgnoreNothing<ValueType>::operator()([[maybe_unused]] const ValueType& val) const noexcept
{
    return false;
}

} // namespace dataflow::channels::ignorePredicates
