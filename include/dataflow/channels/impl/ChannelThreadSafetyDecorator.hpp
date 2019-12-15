#include "../ChannelThreadSafetyDecorator.h"

namespace dataflow::channels {

template <class CHANNEL>
void ChannelThreadSafetyDecorator<CHANNEL>::attachSinkBlock(BlockIf* block)
{
    chan_.attachSinkBlock(block);
}

template <class CHANNEL>
void ChannelThreadSafetyDecorator<CHANNEL>::attachSourceBlock(BlockIf* block)
{
    chan_.attachSourceBlock(block);
}

template <class CHANNEL>
std::optional<typename CHANNEL::ValueType> ChannelThreadSafetyDecorator<CHANNEL>::pop()
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.pop();
}

template <class CHANNEL>
void ChannelThreadSafetyDecorator<CHANNEL>::push(typename CHANNEL::ValueType&& data)
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.push(std::forward<ValueType>(data));
}

template <class CHANNEL>
[[nodiscard]] bool ChannelThreadSafetyDecorator<CHANNEL>::dataAvailable() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.dataAvailable();
}

template <class CHANNEL>
[[nodiscard]] bool ChannelThreadSafetyDecorator<CHANNEL>::dataAssignable() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.dataAssignable();
}

template <class CHANNEL>
std::size_t ChannelThreadSafetyDecorator<CHANNEL>::size() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.size();
}

template <class CHANNEL>
std::size_t ChannelThreadSafetyDecorator<CHANNEL>::max_size() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.max_size();
}

} // namespace df
