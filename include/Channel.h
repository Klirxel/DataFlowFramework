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

template <typename T> void Channel<T>::attachSinkBlock(BlockIf *block) {
  outputBlock_ = block;
}

template <typename T> T Channel<T>::pop() {
  T elem = std::move(data_.front());
  data_.pop();
  return elem;
}

template <typename T> void Channel<T>::push(T &&data) {
  data_.push(std::forward<T>(data));

  if (outputBlock_ != nullptr && outputBlock_->readyForExecution()) {
    outputBlock_->execute();
  };
}

template <typename T> bool Channel<T>::empty() const { return data_.empty(); }

} // namespace df
