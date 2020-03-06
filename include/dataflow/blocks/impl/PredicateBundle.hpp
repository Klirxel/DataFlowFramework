#include "../PredicateBundle.h"

namespace dataflow::blocks {

template <typename... Predicates>
constexpr PredicateBundle<Predicates...>::PredicateBundle(const Predicates&... predicates) noexcept
    : predicates_ { predicates... }
{
}

template <typename... Predicates>
template <typename... PredicateInput>
std::array<bool, sizeof...(Predicates)>
PredicateBundle<Predicates...>::operator()(const PredicateInput&... predicateInput) const
{

    return eval(std::index_sequence_for<PredicateInput...> {}, predicateInput...);
}

template <typename... Predicates>
template <typename... PredicateInput, size_t... Is>
[[nodiscard]] std::array<bool, sizeof...(Predicates)>
PredicateBundle<Predicates...>::eval(
    std::index_sequence<Is...> /*unused*/, const PredicateInput&... predicateInput) const
{
    return { (std::get<Is>(predicates_)(predicateInput))... };
}

} // namespace dataflow::blocks
