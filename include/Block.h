#include <functional>
#include <type_traits>

namespace df {

template <typename OPERATOR, typename... INPUT> class Block {

public:
  using OUTPUT = std::invoke_result_t<OPERATOR, INPUT...>;

  constexpr Block(OPERATOR &op) noexcept : op_(op){};
  
  inline OUTPUT operator()(const INPUT &... input) noexcept {
    return std::invoke(op_, input...);
  }

  inline OUTPUT operator()(INPUT &&... input) noexcept {
    return std::invoke(op_, std::forward(input)...);
  }

private:
  OPERATOR &op_;
};

} // namespace df
