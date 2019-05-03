#pragma once

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
    virtual T pop() = 0;
    virtual void push(T&&) = 0;
    virtual bool dataAvailable() const = 0;
    virtual bool dataAssignable() const = 0;
};

} // namespace df
