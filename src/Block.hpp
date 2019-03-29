#include "Block.h"

namespace df {

template <typename OPERATOR, typename EXECUTOR, typename... INPUT>
constexpr Block<OPERATOR, EXECUTOR, INPUT...>::Block(OPERATOR &op) noexcept
    : executor_(op) {}

template <typename OPERATOR, typename EXECUTOR, typename... INPUT>
constexpr typename Block<OPERATOR, EXECUTOR, INPUT...>::OUTPUT
Block<OPERATOR, EXECUTOR, INPUT...>::
operator()(const INPUT &... input) noexcept {
  return executor_(input...);
}

template <typename OPERATOR, typename EXECUTOR, typename... INPUT>
constexpr typename Block<OPERATOR, EXECUTOR, INPUT...>::OUTPUT
Block<OPERATOR, EXECUTOR, INPUT...>::operator()(INPUT &&... input) noexcept {
  return executor_(std::forward(input)...);
}

} // namespace df
