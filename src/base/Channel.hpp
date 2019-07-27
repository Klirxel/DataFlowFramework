#include <algorithm>

#include "Channel.h"

namespace df::base {

template <typename T>
constexpr void Channel<T>::attachSinkBlock(BlockIf* sinkBlock) noexcept
{
    sinkBlockList_.push_back(sinkBlock);
}

template <typename T>
constexpr void Channel<T>::attachSourceBlock(BlockIf* sourceBlock) noexcept
{
    sourceBlockList_.push_back(sourceBlock);
}

template <typename T>
std::optional<T> Channel<T>::pop()
{
    std::optional<T> data;

    if (not data_.empty()) {
        data = std::move(data_.front());
        data_.pop();
        notify(sourceBlockList_.begin(), sourceBlockList_.end()); //readyToTakeData
    }

    return data;
}

template <typename T>
void Channel<T>::push(T&& data)
{
    data_.push(std::forward<T>(data));
    notify(sinkBlockList_.begin(), sinkBlockList_.end()); //readyToDeliverData
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

template <typename T>
std::size_t Channel<T>::size() const
{
    return data_.size();
}

template <typename T>
std::size_t Channel<T>::max_size() const
{
    return std::numeric_limits<size_t>::max();
}

template <typename T>
template <typename InputIter>
void Channel<T>::notify(InputIter blockListBegin, InputIter blockListEnd)
{
    auto notifyBlockIfReady = [](BlockIf* block) {
        if (block->readyForExecution()) {
            block->execute();
        };
    };

    //note: inform all block strategy. Perhaps there is a more elegant way.
    std::for_each(blockListBegin, blockListEnd, notifyBlockIfReady);
}

} // namespace df
