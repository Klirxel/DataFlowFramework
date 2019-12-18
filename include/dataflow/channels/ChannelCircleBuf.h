#pragma once

#include "ChannelBase.h"
#include <boost/circular_buffer.hpp>

namespace dataflow::channels {

template <typename ValueType, std::size_t Size>
class ChannelCircleBufContainer : public dataContainers::ChannelDataContainerIf<ValueType> {

public:
    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    boost::circular_buffer<ValueType> data_ { Size };
};

template <typename ValueType, std::size_t Size>
using ChannelCircleBuf = ChannelBase<ChannelCircleBufContainer<ValueType, Size>>;

} // namespace df

#include "impl/ChannelCircleBuf.hpp"
