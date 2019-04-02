#include "Channel.h"

namespace df {

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
