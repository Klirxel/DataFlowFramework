#define BOOST_TEST_MODULE test_block_output_predicate
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <dataflow/blocks/Block.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

struct OutputOnlyEven {

    template <typename... T>
    constexpr std::array<bool, sizeof...(T)> operator()(const T&... inputPack) const
    {
        auto isEven = [](const auto& number) { return number % 2 == 0; };
        return { isEven(inputPack)... };
    }
};

constexpr std::tuple<int> passThrough(int val) noexcept
{
    return std::tuple<int> { val };
}

BOOST_AUTO_TEST_CASE(BasicOutputPredicate)
{
    Channel<int> chanIn, chanOut;

    ExecutorSeq executor;

    Block block {
        ChannelBundle { chanIn },
        passThrough,
        ChannelBundle { chanOut },
        executor,
        OutputOnlyEven {}
    };

    const size_t cycles = 101;

    for (size_t cycle = 0; cycle < cycles; ++cycle) {
        chanIn.push(cycle);
    };

    const size_t cyclesEven = cycles % 2 == 0 ? cycles / 2 : cycles / 2 + 1;

    BOOST_CHECK_EQUAL(chanOut.size(), cyclesEven);

    for (size_t i = 0; i < cyclesEven; ++i) {
        BOOST_CHECK_EQUAL(chanOut.pop().value() % 2, 0);
    }
}
