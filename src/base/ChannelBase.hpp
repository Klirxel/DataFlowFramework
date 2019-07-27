#include <algorithm>

#include "ChannelBase.h"

namespace df::base {

template <template <typename> class ChannelDataContainer, typename ValueType>
constexpr void ChannelBase<ChannelDataContainer, ValueType>::attachSinkBlock(BlockIf* sinkBlock) noexcept
{
    sinkBlockList_.push_back(sinkBlock);
}

template <template <typename> class ChannelDataContainer, typename ValueType>
constexpr void ChannelBase<ChannelDataContainer, ValueType>::attachSourceBlock(BlockIf* sourceBlock) noexcept
{
    sourceBlockList_.push_back(sourceBlock);
}

template <template <typename> class ChannelDataContainer, typename ValueType>
std::optional<ValueType> ChannelBase<ChannelDataContainer, ValueType>::pop()
{
    std::optional<ValueType> value = dataContainer_.pop();

    if (value) {
        notify(sourceBlockList_.begin(), sourceBlockList_.end()); //readyToTakeData
    }

    return value;
}

template <template <typename> class ChannelDataContainer, typename ValueType>
void ChannelBase<ChannelDataContainer, ValueType>::push(ValueType&& data)
{
    dataContainer_.push(std::forward<ValueType>(data));
    notify(sinkBlockList_.begin(), sinkBlockList_.end()); //readyToDeliverData
}

template <template <typename> class ChannelDataContainer, typename ValueType>
bool ChannelBase<ChannelDataContainer, ValueType>::dataAvailable() const
{
    const bool dataAvailable = dataContainer_.size() > 0;
    return dataAvailable;
}

template <template <typename> class ChannelDataContainer, typename ValueType>
bool ChannelBase<ChannelDataContainer, ValueType>::dataAssignable() const
{
    const bool dataAssignable = dataContainer_.size() < dataContainer_.max_size();
    return dataAssignable;
}

template <template <typename> class ChannelDataContainer, typename ValueType>
std::size_t ChannelBase<ChannelDataContainer, ValueType>::size() const
{
    return dataContainer_.size();
}

template <template <typename> class ChannelDataContainer, typename ValueType>
std::size_t ChannelBase<ChannelDataContainer, ValueType>::max_size() const
{
    return dataContainer_.max_size();
}

template <template <typename> class ChannelDataContainer, typename ValueType>
template <typename InputIter>
void ChannelBase<ChannelDataContainer, ValueType>::notify(InputIter blockListBegin, InputIter blockListEnd)
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
