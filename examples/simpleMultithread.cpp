/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>

#include <dataflow/dataflow.h>
using namespace dataflow;


//Simple example showing multithread capability.
//
//  DataflowGraph:
//
//                                  Worker1
//  NumberGenerator ---channel1 --> Worker2 ---channel2-->  ConsoleWriter
//                                  Worker3
//
int main()
{
    //Definition Channels
    ChannelThreadSafe<int> channel1;
    ChannelThreadSafe<int> channel2;

    //Definiton Executor
    const auto threads = 4;
    const auto inactivityBeforeDestruction = 200ms;
    ExecutorMultithread executor { threads, inactivityBeforeDestruction };

    //Definiton NumberGenerator
    auto counter = [count = 0]() mutable { return count++; };
    GeneratorBlock numberGenerator { counter, ChannelBundle { channel1 } };

    //Definition Worker 1/2/3
    constexpr auto delay = 300ms;
    constexpr auto worker = [delay](int val) { std::this_thread::sleep_for(delay); return val; };
    Block worker1 { ChannelBundle { channel1 }, worker, ChannelBundle { channel2 }, executor };
    Block worker2 { ChannelBundle { channel1 }, worker, ChannelBundle { channel2 }, executor };
    Block worker3 { ChannelBundle { channel1 }, worker, ChannelBundle { channel2 }, executor };

    //Definition ConsoleWriter
    constexpr auto writer = [](int val) { std::cout << "Output: " << val << '\n'; };
    SinkBlock consoleWriter { ChannelBundle { channel2 }, writer, executor };

    //Start Generator
    const auto period = 100ms;
    const auto offset = 0ms;
    const auto cycles = 10;
    numberGenerator.start(period, offset, cycles);
}
