#pragma once

#include <optional>
#include <type_traits>
#include <vector>

#include "../blocks/BlockIf.h"
#include "../channels/ChannelIf.h"
#include "dataContainers/ChannelDataContainerIf.h"

using namespace dataflow::blocks;
using namespace dataflow::channels;

namespace dataflow::channels {

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

    static_assert(std::is_base_of_v<dataContainers::ChannelDataContainerIf<typename ChannelDataContainer::ValueType>, ChannelDataContainer>,
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

#include "impl/ChannelBase.hpp"
