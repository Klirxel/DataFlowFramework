#include "TransmissionAnalyser.h"

namespace dataflow::tools {

inline TransmissionAnalyser::TransmissionAnalyser(const TransmissionAnalyser& other) noexcept
    : calls(other.calls)
{
    ++callsCopyCtor;
}

inline TransmissionAnalyser::TransmissionAnalyser(TransmissionAnalyser&& other) noexcept
    : calls(other.calls)
{
    ++callsMoveCtor;
}

inline TransmissionAnalyser& TransmissionAnalyser::operator=(const TransmissionAnalyser& other) noexcept
{
    calls = other.calls;
    ++callsCopyAssOp;
    return *this;
}

inline TransmissionAnalyser& TransmissionAnalyser::operator=(TransmissionAnalyser&& other) noexcept
{
    calls = other.calls;
    ++callsMoveAssOp;
    return *this;
}

inline TransmissionAnalyser::~TransmissionAnalyser() noexcept
{
    std::lock_guard lock { mutex_ };
    ++callsDestructor;
}

}
// namespace df::base
