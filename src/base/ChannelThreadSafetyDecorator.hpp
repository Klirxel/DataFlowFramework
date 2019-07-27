#include "ChannelThreadSafetyDecorator.h"

namespace df::base {

template <typename T, template <typename> class CHANNEL>
void ChannelThreadSafetyDecorator<T, CHANNEL>::attachSinkBlock(BlockIf* block)
{
    chan_.attachSinkBlock(block);
}

template <typename T, template <typename> class CHANNEL>
void ChannelThreadSafetyDecorator<T, CHANNEL>::attachSourceBlock(BlockIf* block)
{
    chan_.attachSourceBlock(block);
}

template <typename T, template <typename> class CHANNEL>
std::optional<T> ChannelThreadSafetyDecorator<T, CHANNEL>::pop()
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.pop();
}

template <typename T, template <typename> class CHANNEL>
void ChannelThreadSafetyDecorator<T, CHANNEL>::push(T&& data)
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.push(std::forward<T>(data));
}

template <typename T, template <typename> class CHANNEL>
[[nodiscard]] bool ChannelThreadSafetyDecorator<T, CHANNEL>::dataAvailable() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.dataAvailable();
}

template <typename T, template <typename> class CHANNEL>
[[nodiscard]] bool ChannelThreadSafetyDecorator<T, CHANNEL>::dataAssignable() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.dataAssignable();
}

template <typename T, template <typename> class CHANNEL>
std::size_t ChannelThreadSafetyDecorator<T, CHANNEL>::size() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.size();
}

template <typename T, template <typename> class CHANNEL>
std::size_t ChannelThreadSafetyDecorator<T, CHANNEL>::max_size() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.max_size();
}

} // namespace df
