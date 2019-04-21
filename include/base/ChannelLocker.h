#pragma once

#include <mutex>
#include <type_traits>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename T>
class ChannelLocker : public ChannelIf<T> {

public:
    constexpr ChannelLocker(ChannelIf<T>& /*chan*/) noexcept;

    void attachSinkBlock(BlockIf* /*block*/) override;
    void attachSourceBlock(BlockIf* /*block*/) override;

    T pop() override;
    void push(T&& /*data*/) override;
    bool dataAvailable() const override;
    bool dataAssignable() const override;

private:
    mutable std::mutex mutex_;
    ChannelIf<T>& chan_;
};

} // namespace df

#include "ChannelLocker.hpp"
