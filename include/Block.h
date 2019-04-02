#pragma once

#include <type_traits>

#include "Channel.h"

namespace df {

template <typename T_IN, typename OPERATOR, typename T_OUT>
class Block : public BlockIf {

public:
  Block(Channel<T_IN> &chanIn, OPERATOR &op, Channel<T_OUT> &chanOut);

  bool readyForExecution() override;

  void execute() override;

private:
  Channel<T_IN> &chanIn_;
  OPERATOR &op_;
  Channel<T_OUT> &chanOut_;
};

} // namespace df

#include "Block.hpp"
