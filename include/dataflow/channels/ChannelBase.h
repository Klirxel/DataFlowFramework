#pragma once

#include <optional>
#include <type_traits>
#include <vector>

#include "BlockIf.h"
#include "ChannelIf.h"

namespace df::base {

template <typename ValueType_>
struct ChannelDataContainerIf {

    using ValueType = ValueType_;

    virtual std::optional<ValueType> pop() = 0;
    virtual void push(ValueType&& /*data*/) = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual std::size_t max_size() const = 0;
};

enum class TriggerPolicy {
    triggerSink,
    triggerSource,
    triggerAll,
    triggerNone
};

template <typename ValueType>
struct IgnoreNothing {

    [[nodiscard]] constexpr bool operator()([[maybe_unused]] const ValueType& val) const noexcept
    {
        return false;
    };
};

template <typename ValueType>
struct IgnoreDefaults {

    [[nodiscard]] constexpr bool operator()(const ValueType& val) const
    {
        return val == ValueType {};
    };
};

template <class ChannelDataContainer,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerAll,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = IgnoreNothing<typename ChannelDataContainer::ValueType>>
class ChannelBase : public ChannelIf<typename ChannelDataContainer::ValueType> {

    static_assert(std::is_base_of_v<ChannelDataContainerIf<typename ChannelDataContainer::ValueType>, ChannelDataContainer>,
        "ChannelDataContainer has to be derived form ChannelDataContainerIf");

public:
    using ValueType = typename ChannelDataContainer::ValueType;

    constexpr void attachSinkBlock(BlockIf* /*block*/) noexcept override;
    constexpr void attachSourceBlock(BlockIf* /*block*/) noexcept override;
    std::optional<ValueType> pop() override;
    void push(ValueType&& /*data*/) override;
    [[nodiscard]] bool dataAvailable() const override;
    [[nodiscard]] bool dataAssignable() const override;
    [[nodiscard]] std::size_t size() const override;
    [[nodiscard]] std::size_t max_size() const override;

private:
    void notify(std::vector<BlockIf*>& blockList);
    void notifySourceBlockList();
    void notifySinkBlockList();

    std::vector<BlockIf*> sinkBlockList_;
    std::vector<BlockIf*> sourceBlockList_;
    ChannelDataContainer dataContainer_;
};

} // namespace df

#include "ChannelBase.hpp"
