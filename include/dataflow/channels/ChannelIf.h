/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once

#include <mutex>
#include <optional>
#include <type_traits>

#include "../blocks/BlockIf.h"


namespace dataflow::channels {

using dataflow::blocks::BlockIf;

/**
 * @brief Generic interface for channels.
 *
 * @remark
 * - Should be used as a generic interface to address channels.
 */
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
    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual std::size_t max_size() const = 0;

    [[nodiscard]] constexpr std::mutex& getLock() noexcept;

private:
    mutable std::mutex lock;
};

} // namespace dataflow::channels

#include "impl/ChannelIf.hpp"
