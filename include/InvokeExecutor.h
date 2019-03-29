#pragma once

#include <functional>

namespace df {
template <typename OPERATOR, typename... INPUT> class InvokeExecutor {

public:
  using OUTPUT = std::invoke_result_t<OPERATOR, INPUT...>;

  constexpr InvokeExecutor(OPERATOR &op) noexcept;

  constexpr OUTPUT operator()(const INPUT &... input) noexcept;
  constexpr OUTPUT operator()(INPUT &&... input) noexcept;

private:
  OPERATOR &op_;
};

} // namespace df

#include "InvokeExecutor.hpp"
