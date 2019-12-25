#define BOOST_TEST_MODULE testExecutorMultihread_1
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <set>

#include <dataflow/blocks/Block.h>
#include <dataflow/blocks/GeneratorBlock.h>
#include <dataflow/blocks/SinkBlock.h>
#include <dataflow/channels/ChannelThreadSave.h>
#include <dataflow/executors/ExecutorMultithread.h>

using namespace dataflow::blocks;
using namespace dataflow::channels;
using namespace dataflow::executors;

struct Counter {

    int operator()() noexcept
    {
        ////std::cout << "Counter: Input data " << count << std::endl;
        return count++;
    };

    int count { 0 };
};

const auto multiply2Delay = 8ms;

template <size_t index>
int multiply2(int input) noexcept
{
    std::this_thread::sleep_for(multiply2Delay);

    const int inputMul2 = 2 * input;
    std::cout << "multiply2Unit-" << index << ": 2 * " << input << " = " << inputMul2 << '\n';
    return inputMul2;
}

struct DataStorage {

    void operator()(int value)
    {
        data.push_back(value);
    };

    std::vector<int> data;
};

BOOST_AUTO_TEST_CASE(BlockBasicAddExample)
{
    Counter counter;
    DataStorage dataStorage;

    ChannelThreadSafe<int> inputChan;
    ChannelThreadSafe<int> chanRes;

    GeneratorBlock inputGenerator { counter, ChannelBundle { inputChan } };

    const size_t threads = 9;
    ExecutorMultithread execMultihread { threads };

    Block multiplyBlock1 { ChannelBundle { inputChan }, multiply2<1>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock2 { ChannelBundle { inputChan }, multiply2<2>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock3 { ChannelBundle { inputChan }, multiply2<3>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock4 { ChannelBundle { inputChan }, multiply2<4>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock5 { ChannelBundle { inputChan }, multiply2<5>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock6 { ChannelBundle { inputChan }, multiply2<6>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock7 { ChannelBundle { inputChan }, multiply2<7>, ChannelBundle { chanRes }, execMultihread };
    Block multiplyBlock8 { ChannelBundle { inputChan }, multiply2<8>, ChannelBundle { chanRes }, execMultihread };

    SinkBlock dataStorageBlock { ChannelBundle { chanRes }, dataStorage, execMultihread };

    const auto starttime = std::chrono::system_clock::now();
    const size_t cycles = 1000;
    const auto period = 1ms;
    const auto offset = 0ms;
    inputGenerator.start(period, offset, cycles);
    inputGenerator.wait();
    execMultihread.stop();

    const auto stoptime = std::chrono::system_clock::now();
    const auto processingDuration = stoptime - starttime;

    std::cout << "ProcessingTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(processingDuration).count() << "ms \n";
    std::cout << "ProcessingTime (singleThread): " << cycles * multiply2Delay.count() << " ms \n";
    std::cout << "ProcessingTime (multiThread ideal): " << cycles * multiply2Delay.count() / threads << " ms \n";

    BOOST_CHECK_EQUAL(inputChan.dataAvailable(), false);

    std::set<size_t> resultsUnordered {};
    for (size_t cycle = 0; cycle < cycles; ++cycle) {
        resultsUnordered.insert(2 * cycle);
    }

    for (const auto& resultOfCycle : dataStorage.data) {
        BOOST_CHECK_EQUAL(resultsUnordered.count(resultOfCycle), 1);
        resultsUnordered.erase(resultOfCycle);
    }

    for (auto missedElem : resultsUnordered) {
        std::cout << "MissedElem" << missedElem << '\n';
    }

    BOOST_CHECK_EQUAL(chanRes.dataAvailable(), false);
}
