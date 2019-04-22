#include "Channel.h"

namespace df::base {

template <typename T>
constexpr void Channel<T>::attachSinkBlock(BlockIf* block) noexcept
{
    sinkBlock_ = block;
}

template <typename T>
constexpr void Channel<T>::attachSourceBlock(BlockIf* block) noexcept
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
bool Channel<T>::dataAvailable() const
{
    return not data_.empty();
}

template <typename T>
bool Channel<T>::dataAssignable() const
{
    return true;
}

inline void notify(BlockIf* block)
{
    if (block != nullptr && block->readyForExecution()) {
        block->execute();
    };
}

} // namespace df
