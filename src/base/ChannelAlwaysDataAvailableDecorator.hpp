#include <limits>

#include "ChannelAlwaysDataAvailableDecorator.h"


namespace df::base {

template <typename T, template <typename> class CHANNEL>
void ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::attachSinkBlock(BlockIf* block)
{
    chan_.attachSinkBlock(block);
}

template <typename T, template <typename> class CHANNEL>
void ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::attachSourceBlock(BlockIf* block)
{
    chan_.attachSourceBlock(block);
}

template <typename T, template <typename> class CHANNEL>
std::optional<T> ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::pop()
{
    return chan_.dataAvailable() ? chan_.pop() : std::optional<T> { T {} };
}

template <typename T, template <typename> class CHANNEL>
void ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::push(T&& data)
{
    return chan_.push(std::forward<T>(data));
}

template <typename T, template <typename> class CHANNEL>
bool ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::dataAvailable() const
{
    return true;
}

template <typename T, template <typename> class CHANNEL>
bool ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::dataAssignable() const
{
    return chan_.dataAssignable();
}

template <typename T, template <typename> class CHANNEL>
[[nodiscard]] constexpr size_t ChannelAlwaysDataAvailableDecorator<T, CHANNEL>::size() const
{
    return std::numeric_limits<size_t>::max();
}

} // namespace df
