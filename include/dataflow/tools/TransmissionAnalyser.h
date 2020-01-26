/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#include <array>
#include <mutex>

namespace dataflow::tools {

/**
 * @brief Inspection datatype. 
 *
 * @details
 * - Datatype that can be used for
 *   analysing the amount of
 *   contruction, move and copy operation utilized
 *   by the dataflow framework.
 * - Use it as a datatype of an dataflow graph,
 *   execute the dataflow graph and then read
 *   out the member variables. 
 * - Usage example see \ref ptest_transmissionAnalyses.cpp.
 */
struct TransmissionAnalyser {

    constexpr TransmissionAnalyser() noexcept = default;

    constexpr TransmissionAnalyser(const TransmissionAnalyser& other) noexcept;

    constexpr TransmissionAnalyser(TransmissionAnalyser&& other) noexcept;

    constexpr TransmissionAnalyser& operator=(const TransmissionAnalyser& other) noexcept;

    constexpr TransmissionAnalyser& operator=(TransmissionAnalyser&& other) noexcept;

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
