#include <algorithm>

#include "../ChannelCircleBuf.h"

namespace dataflow::channels {

template <typename ValueType, std::size_t Size>
std::optional<ValueType> ChannelCircleBufContainer<ValueType, Size>::pop()
{
    std::optional<ValueType> data;

    if (not data_.empty()) {
        data = std::move(data_.front());
        data_.pop_front();
    }

    return data;
}

template <typename ValueType, std::size_t Size>
void ChannelCircleBufContainer<ValueType, Size>::push(ValueType&& data)
{
    data_.push_back(std::forward<ValueType>(data));
}

template <typename ValueType, std::size_t Size>
std::size_t ChannelCircleBufContainer<ValueType, Size>::size() const
{
    return data_.size();
}

template <typename ValueType, std::size_t Size>
std::size_t ChannelCircleBufContainer<ValueType, Size>::max_size() const
{
    return Size;
}

} // namespace df
