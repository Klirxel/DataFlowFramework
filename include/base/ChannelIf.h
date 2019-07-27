#pragma once

#include <mutex>
#include <optional>
#include <type_traits>

#include "BlockIf.h"

namespace df::base {

template <typename T>
class ChannelIf {

    static_assert(std::is_move_constructible_v<T>,
        "T has to be move constructible");

public:
    using ValueType = T;

    virtual void attachSinkBlock(BlockIf*) = 0;
    virtual void attachSourceBlock(BlockIf*) = 0;
    virtual std::optional<T> pop() = 0;
    virtual void push(T&&) = 0;
    [[nodiscard]] virtual bool dataAvailable() const = 0;
    [[nodiscard]] virtual bool dataAssignable() const = 0;

    std::mutex lock;
};

} // namespace df
