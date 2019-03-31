#pragma once

#include <memory>
#include <queue>

namespace df {

class BlockIf {
public:
  virtual bool readyForExecution();
  virtual void execute();
};

template <typename T> class Channel {

public:
  void attachSinkBlock(std::shared_ptr<BlockIf>);
  T pop();
  void push(const T &);
  void push(T &&);

private:
  std::shared_ptr<BlockIf> outputBlock_;
  std::queue<T> data_;
};

template <typename T>
void Channel<T>::attachSinkBlock(std::shared_ptr<BlockIf> block) {
  outputBlock_ = block;
}

template <typename T> T Channel<T>::pop() {
  T elem = std::move(data_.back());
  data_.pop();
  return elem;
}

template <typename T> void Channel<T>::push(T &&data) {
  data_.push(std::forward(data));

  if (outputBlock_->readyForExecution()) {
    outputBlock_->execute();
  };
}

template <typename T> void Channel<T>::push(const T &data) {
  data_.push(data);
  if (outputBlock_->readyForExecution()) {
    outputBlock_->execute();
  };
}

} // namespace df
