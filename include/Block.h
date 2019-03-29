#include <type_traits>

namespace df {

template <typename OPERATOR, typename... INPUT> class Block {

public:
  using OUTPUT = std::invoke_result_t<OPERATOR, INPUT...>;

  Block(OPERATOR &op) : op_(op){};

  OUTPUT operator()(INPUT... input) { return op_(input...); }

private:
  OPERATOR &op_;
};

} // namespace df
