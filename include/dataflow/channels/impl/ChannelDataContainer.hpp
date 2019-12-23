#include "../dataContainers/ChannelDataContainer.h"

namespace dataflow::channels::dataContainers {

template <typename T>
std::optional<T> ChannelDataContainer<T>::pop()
{
    std::optional<T> data;

    if (not data_.empty()) {
        data = std::move(data_.front());
        data_.pop();
    }

    return data;
}

template <typename T>
void ChannelDataContainer<T>::push(T&& data)
{
    data_.push(std::forward<T>(data));
}

template <typename T>
std::size_t ChannelDataContainer<T>::size() const
{
    return data_.size();
}

template <typename T>
std::size_t ChannelDataContainer<T>::max_size() const
{
    return std::numeric_limits<size_t>::max();
}

} // namespace dataflow::channels:dataContainers
