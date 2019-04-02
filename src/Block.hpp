#include "Block.h"

namespace df {

  template <typename T_IN, typename OPERATOR, typename T_OUT>
  Block<T_IN, OPERATOR, T_OUT>::Block(Channel<T_IN> & chanIn, OPERATOR & op,
                                      Channel<T_OUT> & chanOut)
      : chanIn_(chanIn), op_(op), chanOut_(chanOut) {
    chanIn_.attachSinkBlock(this);
  }

  template <typename T_IN, typename OPERATOR, typename T_OUT>
  bool Block<T_IN, OPERATOR, T_OUT>::readyForExecution() {
    return not chanIn_.empty();
  }

  template <typename T_IN, typename OPERATOR, typename T_OUT>
  void Block<T_IN, OPERATOR, T_OUT>::execute() {
    T_IN input = chanIn_.pop();
    T_OUT output = op_(std::move(input));
    chanOut_.push(std::move(output));
  }

} // namespace df
