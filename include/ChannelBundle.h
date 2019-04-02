#pragma once

#include "ChannelIf.h"

namespace df {

template <typename... T> class ChannelBundle {

public:
  template <size_t I>
  using ChannelValueType = std::tuple_element_t<I, std::tuple<T...>>;

  template <size_t I> using ChannelType = ChannelIf<ChannelValueType<I>>;

  constexpr ChannelBundle(ChannelIf<T> &... channels) noexcept;

  template <size_t I> constexpr ChannelType<I> &at() noexcept;

private:
  std::tuple<ChannelIf<T> &...> channels_;
};

} // namespace df

#include "ChannelBundle.hpp"
