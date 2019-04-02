#pragma once

#include <type_traits>

#include "Channel.h"

namespace df {

template <typename T_IN, typename OPERATOR, typename T_OUT>
class Block : public BlockIf {

public:
  Block(Channel<T_IN> &chanIn, OPERATOR &op, Channel<T_OUT> &chanOut)
      : chanIn_(chanIn), op_(op), chanOut_(chanOut) {
    chanIn_.attachSinkBlock(this);
  };

  bool readyForExecution() override { return not chanIn_.empty(); };

  void execute() override {
    T_IN input = chanIn_.pop();
    T_OUT output = op_(std::move(input));
    chanOut_.push(std::move(output));
  };

private:
  Channel<T_IN> &chanIn_;
  OPERATOR &op_;
  Channel<T_OUT> &chanOut_;
};


} // namespace df

#include "Block.hpp"
