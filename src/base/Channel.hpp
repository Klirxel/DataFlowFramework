#include "Channel.h"

namespace df::base {

template <typename T>
void Channel<T>::attachSinkBlock(BlockIf* block) noexcept
{
    sinkBlock_ = block;
}

template <typename T>
void Channel<T>::attachSourceBlock(BlockIf* block) noexcept
{
    sourceBlock_ = block;
}

template <typename T>
T Channel<T>::pop()
{
    T elem = std::move(data_.front());
    data_.pop();

    notify(sourceBlock_); //readyToTakeData

    return elem;
}

template <typename T>
void Channel<T>::push(T&& data)
{
    data_.push(std::forward<T>(data));
    notify(sinkBlock_); //readyToDeliverData
}

template <typename T>
bool Channel<T>::empty() const { return data_.empty(); }

template <typename T>
size_t Channel<T>::size() const { return data_.size(); }

inline void notify(BlockIf* block)
{
    if (block != nullptr && block->readyForExecution()) {
        block->execute();
    };
}

} // namespace df
