#pragma once

#include <type_traits>

#include "InvokeExecutor.h"

namespace df {

template <typename OPERATOR, typename EXECUTOR, typename... INPUT> class Block {

public:
  using OUTPUT = std::invoke_result_t<OPERATOR, INPUT...>;

  constexpr Block(OPERATOR &op) noexcept;

  constexpr OUTPUT operator()(const INPUT &... input) noexcept;

  constexpr OUTPUT operator()(INPUT &&... input) noexcept;

private:
  EXECUTOR executor_;
};

template <typename OPERATOR, typename... INPUT>
using SyncBlock = Block<OPERATOR, InvokeExecutor<OPERATOR, INPUT...>, INPUT...>;

} // namespace df

#include "Block.hpp"
