/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <boost/circular_buffer.hpp>

#include "ChannelDataContainerIf.h"

namespace dataflow::channels::dataContainers {

/**
 * @brief Circular buffer container 
 */
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

} // namespace dataflow::channels::dataContainers

#include "../impl/ChannelCircleBufContainer.hpp"
