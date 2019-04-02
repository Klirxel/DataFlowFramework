#pragma once

#include <memory>
#include <queue>
#include <type_traits>
#include <utility>

#include "BlockIf.h"

namespace df {

template <typename T> class Channel {

  static_assert(std::is_move_constructible_v<T>,
                "T has to be move constructible");

public:
  void attachSinkBlock(BlockIf *);
  T pop();
  void push(T &&);
  bool empty() const;

private:
  BlockIf *outputBlock_{};
  std::queue<T> data_;
};

} // namespace df

#include "Channel.hpp"
