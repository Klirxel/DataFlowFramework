#pragma once

#include <optional>
#include <type_traits>

namespace dataflow::channels::dataContainers {

template <typename ValueType_>
struct ChannelDataContainerIf {

    static_assert(std::is_move_constructible_v<ValueType_>, "Value type has to be move constructible.");
    static_assert(std::is_move_assignable_v<ValueType_>, "Value type has to be move assignable.");

    using ValueType = ValueType_;

    virtual std::optional<ValueType> pop() = 0;
    virtual void push(ValueType&& data) = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual std::size_t max_size() const = 0;
};

} // namespace dataflow::channels::dataContainers
