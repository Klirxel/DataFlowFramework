#include <functional>
#include <type_traits>

namespace df {

template <typename OPERATOR, typename... INPUT> class InvokeExecutor {

public:
  using OUTPUT = std::invoke_result_t<OPERATOR, INPUT...>;

  constexpr InvokeExecutor(OPERATOR& op) noexcept: op_(op){};

  constexpr OUTPUT operator()(const INPUT &... input) noexcept {
    return std::invoke(op_, input...);
  };

  constexpr OUTPUT operator()(INPUT &&... input) noexcept {
    return std::invoke(op_, std::forward(input)...);
  };

private:
  OPERATOR& op_;
};

template <typename OPERATOR, typename EXECUTOR, typename... INPUT> class Block {

public:
  using OUTPUT = std::invoke_result_t<OPERATOR, INPUT...>;

  constexpr Block(OPERATOR &op) noexcept : executor_(op){};

  inline OUTPUT operator()(const INPUT &... input) noexcept {
    return executor_(input...);
  }

  inline OUTPUT operator()(INPUT &&... input) noexcept {
    return executor_(std::forward(input)...);
  }

private:
  EXECUTOR executor_;
};

template <typename OPERATOR, typename... INPUT>
using SyncBlock =
    Block<OPERATOR, InvokeExecutor<OPERATOR, INPUT...>, INPUT...>;

} // namespace df
