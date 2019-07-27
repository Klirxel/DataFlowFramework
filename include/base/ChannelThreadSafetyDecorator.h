#pragma once

#include <mutex>
#include <type_traits>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename T, template <typename> class CHANNEL>
class ChannelThreadSafetyDecorator : public ChannelIf<T> {

    static_assert(std::is_base_of_v<ChannelIf<T>, CHANNEL<T>>, "CHANNER<T> is not derived from ChannelIf<T>");
    static_assert(std::is_default_constructible_v<CHANNEL<T>>, "CHANNEl<T> is not default constructible.");

public:
    void attachSinkBlock(BlockIf* /*block*/) override;
    void attachSourceBlock(BlockIf* /*block*/) override;

    std::optional<T> pop() override;
    void push(T&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    mutable std::mutex mutex_;
    CHANNEL<T> chan_;
};

} // namespace df

#include "ChannelThreadSafetyDecorator.hpp"
