#pragma once

#include <optional>
#include <type_traits>
#include <vector>

#include "../blocks/BlockIf.h"
#include "../channels/ChannelIf.h"
#include "TriggerPolicy.h"
#include "dataContainers/ChannelDataContainerIf.h"
#include "ignorePredicates/IgnoreNothing.h"

using namespace dataflow::blocks;
using namespace dataflow::channels;

namespace dataflow::channels {

template <class ChannelDataContainer,
    TriggerPolicy triggerPolicyPop = TriggerPolicy::triggerAll,
    TriggerPolicy triggerPolicyPush = TriggerPolicy::triggerSink,
    typename IgnorePredicate = ignorePredicates::IgnoreNothing>
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
