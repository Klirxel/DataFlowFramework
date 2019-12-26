#pragma once

#include <queue>

#include "ChannelDataContainerIf.h"

namespace dataflow::channels::dataContainers {

/**
 * @brief Unlimited data container.
 */
template <typename ValueType>
class ChannelDataContainer : public dataContainers::ChannelDataContainerIf<ValueType> {

public:
    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    std::queue<ValueType> data_;
};

} // namespace dataflow::channels::dataContainers

#include "../impl/ChannelDataContainer.hpp"
