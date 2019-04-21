#include "ChannelLocker.h"

namespace df::base {

template <typename T>
constexpr ChannelLocker<T>::ChannelLocker(ChannelIf<T>& chan) noexcept
    : chan_(chan)
{
}

template <typename T>
void ChannelLocker<T>::attachSinkBlock(BlockIf* block)
{
    chan_.attachSinkBlock(block);
}

template <typename T>
void ChannelLocker<T>::attachSourceBlock(BlockIf* block)
{
    chan_.attachSourceBlock(block);
}

template <typename T>
T ChannelLocker<T>::pop()
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.pop();
}

template <typename T>
void ChannelLocker<T>::push(T&& data)
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.push(std::forward<T>(data));
}

template <typename T>
bool ChannelLocker<T>::dataAvailable() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.dataAvailable();
}

template <typename T>
bool ChannelLocker<T>::dataAssignable() const
{
    std::lock_guard<std::mutex> { mutex_ };
    return chan_.dataAssignable();
}

} // namespace df
