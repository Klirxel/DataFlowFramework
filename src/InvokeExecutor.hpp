#include "InvokeExecutor.h"

namespace df {

template <typename OPERATOR, typename... INPUT>
constexpr InvokeExecutor<OPERATOR, INPUT...>::InvokeExecutor(
    OPERATOR &op) noexcept
    : op_(op) {}

template <typename OPERATOR, typename... INPUT>
constexpr typename InvokeExecutor<OPERATOR, INPUT...>::OUTPUT
InvokeExecutor<OPERATOR, INPUT...>::
operator()(const INPUT &... input) noexcept {
  return std::invoke(op_, input...);
}

template <typename OPERATOR, typename... INPUT>
constexpr typename InvokeExecutor<OPERATOR, INPUT...>::OUTPUT
InvokeExecutor<OPERATOR, INPUT...>::operator()(INPUT &&... input) noexcept {
  return std::invoke(op_, std::forward(input)...);
}

} // namespace df
