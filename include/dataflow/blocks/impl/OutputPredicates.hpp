#include "../outputPredicates/OutputAll.h"

namespace dataflow::blocks::outputPredicates {

template <typename... T>
constexpr std::array<bool, sizeof...(T)> OutputAll::operator()([[maybe_unused]] const T&... /*unused*/) const
{
    auto array = std::array<bool, sizeof...(T)> {};
    array.fill(true);
    return array;
}

} // namespace dataflow::blocks::outputPredicates
