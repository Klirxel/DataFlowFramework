#define BOOST_TEST_MODULE testBaseBlock
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <dataflow/blocks/Block.h>
#include <dataflow/channels/Channel.h>
#include <dataflow/executors/ExecutorSeq.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

constexpr int add(int input1, int input2) noexcept { return input1 + input2; }

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Channel<int> input1;
    Channel<int> input2;
    Channel<int> result;

    ExecutorSeq executor {};

    Block block(ChannelBundle(input1, input2), add, ChannelBundle(result), executor);

    input1.push(1);
    input2.push(2);

    BOOST_CHECK_EQUAL(result.dataAvailable(), true);
    BOOST_CHECK_EQUAL(result.size(), 1);
    BOOST_CHECK_EQUAL(result.pop().value(), 3);
}

template <typename... T>
struct OutputOnlyEven {
    [[nodiscard]] constexpr std::array<bool, sizeof...(T)> operator()(const T&... output) const noexcept
    {
        auto isEven = [](const auto& val) {
            return static_cast<bool>(val % 2 == 0);
        };

        return std::array<bool, sizeof...(T)> { isEven(output)... };
    };
};

template <typename... T>
[[nodiscard]] std::tuple<T...> passThrough(T&&... val)
{
    return std::tuple<T...> { std::forward<T>(val)... };
}

BOOST_AUTO_TEST_CASE(BlockOutputPredicateOneChannel)
{
    Channel<int> input;
    Channel<int> output;
    ExecutorSeq executor {};

    Block block { ChannelBundle { input }, passThrough<int>, ChannelBundle { output }, executor, OutputOnlyEven<int> {} };

    input.push(1);
    input.push(2);
    input.push(3);
    input.push(4);

    BOOST_CHECK_EQUAL(output.size(), 2);
    BOOST_CHECK_EQUAL(output.pop().value(), 2);
    BOOST_CHECK_EQUAL(output.pop().value(), 4);
}

BOOST_AUTO_TEST_CASE(BlockOutputPredicateTwoChannel)
{
    Channel<int> input1;
    Channel<int> input2;
    Channel<int> output1;
    Channel<int> output2;

    Channel<int> output;
    ExecutorSeq executor {};

    Block block { ChannelBundle { input1, input2 }, passThrough<int, int>, ChannelBundle { output1, output2 }, executor, OutputOnlyEven<int, int> {} };

    input1.push(0);
    input1.push(1);
    input1.push(2);
    input1.push(3);

    input2.push(1);
    input2.push(2);
    input2.push(3);
    input2.push(4);

    BOOST_REQUIRE_EQUAL(output1.size(), 2);
    BOOST_REQUIRE_EQUAL(output2.size(), 2);
    BOOST_CHECK_EQUAL(output1.pop().value(), 0);
    BOOST_CHECK_EQUAL(output1.pop().value(), 2);
    BOOST_CHECK_EQUAL(output2.pop().value(), 2);
    BOOST_CHECK_EQUAL(output2.pop().value(), 4);
}
