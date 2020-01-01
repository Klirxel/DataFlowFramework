#pragma once
#include <array>
#include <mutex>

namespace dataflow::tools {

struct TransmissionAnalyser {

    constexpr TransmissionAnalyser() noexcept = default;

    inline TransmissionAnalyser(const TransmissionAnalyser& other) noexcept;

    inline TransmissionAnalyser(TransmissionAnalyser&& other) noexcept;

    inline TransmissionAnalyser& operator=(const TransmissionAnalyser& other) noexcept;

    inline TransmissionAnalyser& operator=(TransmissionAnalyser&& other) noexcept;

    inline ~TransmissionAnalyser() noexcept;

    int callsCopyCtor { 0 };
    int callsMoveCtor { 0 };
    int callsCopyAssOp { 0 };
    int callsMoveAssOp { 0 };
    inline static int callsDestructor { 0 };

private:
    constexpr void setVariables(const TransmissionAnalyser& other) noexcept;
    inline static std::mutex mutex_;
};

} //namespace dataflow::tools

#include "impl/TransmissionAnalyser.hpp"
