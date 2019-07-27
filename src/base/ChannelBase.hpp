#include <algorithm>

#include "ChannelBase.h"

namespace df::base {

template <class ChannelDataContainer>
constexpr void ChannelBase<ChannelDataContainer>::attachSinkBlock(BlockIf* sinkBlock) noexcept
{
    sinkBlockList_.push_back(sinkBlock);
}

template <class ChannelDataContainer>
constexpr void ChannelBase<ChannelDataContainer>::attachSourceBlock(BlockIf* sourceBlock) noexcept
{
    sourceBlockList_.push_back(sourceBlock);
}

template <class ChannelDataContainer>
std::optional<typename ChannelDataContainer::ValueType> ChannelBase<ChannelDataContainer>::pop()
{
    std::optional<ValueType> value = dataContainer_.pop();

    if (value) {
        notify(sourceBlockList_.begin(), sourceBlockList_.end()); //readyToTakeData
    }

    return value;
}

template <class ChannelDataContainer>
void ChannelBase<ChannelDataContainer>::push(ValueType&& data)
{
    dataContainer_.push(std::forward<ValueType>(data));
    notify(sinkBlockList_.begin(), sinkBlockList_.end()); //readyToDeliverData
}

template <class ChannelDataContainer>
bool ChannelBase<ChannelDataContainer>::dataAvailable() const
{
    const bool dataAvailable = dataContainer_.size() > 0;
    return dataAvailable;
}

template <class ChannelDataContainer>
bool ChannelBase<ChannelDataContainer>::dataAssignable() const
{
    const bool dataAssignable = dataContainer_.size() < dataContainer_.max_size();
    return dataAssignable;
}

template <class ChannelDataContainer>
std::size_t ChannelBase<ChannelDataContainer>::size() const
{
    return dataContainer_.size();
}

template <class ChannelDataContainer>
std::size_t ChannelBase<ChannelDataContainer>::max_size() const
{
    return dataContainer_.max_size();
}

template <class ChannelDataContainer>
template <typename InputIter>
void ChannelBase<ChannelDataContainer>::notify(InputIter blockListBegin, InputIter blockListEnd)
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
