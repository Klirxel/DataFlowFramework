#include "../TransmissionAnalyser.h"

namespace dataflow::tools {

constexpr TransmissionAnalyser::TransmissionAnalyser(const TransmissionAnalyser& other) noexcept
{
    setVariables(other);
    ++callsCopyCtor;
}

constexpr TransmissionAnalyser::TransmissionAnalyser(TransmissionAnalyser&& other) noexcept
{
    setVariables(other);
    ++callsMoveCtor;
}

constexpr TransmissionAnalyser& TransmissionAnalyser::operator=(const TransmissionAnalyser& other) noexcept
{
    setVariables(other);

    ++callsCopyAssOp;
    return *this;
}

constexpr TransmissionAnalyser& TransmissionAnalyser::operator=(TransmissionAnalyser&& other) noexcept
{
    setVariables(other);

    ++callsMoveAssOp;
    return *this;
}

inline TransmissionAnalyser::~TransmissionAnalyser() noexcept
{
    std::lock_guard lock { mutex_ };
    ++callsDestructor;
}

constexpr void TransmissionAnalyser::setVariables(const TransmissionAnalyser& other) noexcept
{
    callsCopyCtor = other.callsCopyCtor;
    callsMoveCtor = other.callsMoveCtor;
    callsCopyAssOp = other.callsCopyAssOp;
    callsMoveAssOp = other.callsMoveAssOp;
}

}
// namespace df::base
