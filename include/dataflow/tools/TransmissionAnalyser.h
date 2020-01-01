#pragma once
#include <array>
#include <mutex>

namespace dataflow::tools {

struct TransmissionAnalyser {

    TransmissionAnalyser() = default;

    inline TransmissionAnalyser(const TransmissionAnalyser& other) noexcept;

    inline TransmissionAnalyser(TransmissionAnalyser&& other) noexcept;

    inline TransmissionAnalyser& operator=(const TransmissionAnalyser& other) noexcept;

    inline TransmissionAnalyser& operator=(TransmissionAnalyser&& other) noexcept;

    inline ~TransmissionAnalyser() noexcept;

    std::array<int, 4> calls {};

    int& callsCopyCtor { calls.at(0) };
    int& callsMoveCtor { calls.at(1) };
    int& callsCopyAssOp { calls.at(2) };
    int& callsMoveAssOp { calls.at(3) };
    inline static int callsDestructor { 0 };

private:
    inline static std::mutex mutex_;
};

} //namespace df::base

#include "impl/TransmissionAnalyser.hpp"
