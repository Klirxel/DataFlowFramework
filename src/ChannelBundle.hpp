#include "ChannelBundle.h"

namespace df {

template <typename... T>
constexpr ChannelBundle<T...>::ChannelBundle(
    ChannelIf<T> &... channels) noexcept
    : channels_(channels...){};

template <typename... T>
template <size_t I>
constexpr typename ChannelBundle<T...>::template ChannelType<I> &
ChannelBundle<T...>::at() noexcept {
  return std::get<I>(channels_);
}

} // namespace df
// namespace «namespace»
