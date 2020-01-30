/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See acompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <random>

#include <dataflow/dataflow.h>

//Block with multiple inputs and outputs.
//
//  DataflowGraph:
//  RandomGenerator1 --chan1-->|                       | --chan3--> consoleWriter1
//                             |--->  Calculator ----->| --chan4--> consoleWriter2
//  RandomGenerator2 --chan2-->|                       | --chan5--> consoleWriter3
int main()
{
    //Definition Channels
    Channel<int> chan1;
    Channel<int> chan2;
    Channel<int> chan3;
    Channel<int> chan4;
    Channel<int> chan5;

    //Definiton Executor
    ExecutorSeq executor;

    //Definiton random Generator 1/2
    std::random_device rd1;
    std::random_device rd2;
    std::uniform_int_distribution<int> dist1(-100000, 100000);
    std::uniform_int_distribution<int> dist2(-100000, 100000);
    auto randomGen1 = [&dist1, &rd1]() { return dist1(rd1); };
    auto randomGen2 = [&dist2, &rd2]() { return dist2(rd2); };
    GeneratorBlock numberGenerator1 { randomGen1, ChannelBundle { chan1 } };
    GeneratorBlock numberGenerator2 { randomGen2, ChannelBundle { chan2 } };

    //Definition Calculator
    constexpr auto calculate = [](auto val1, auto val2) {
        return std::tuple { val1 + val2, val1 - val2, val1 * val2 };
    };

    Block Calculator { ChannelBundle { chan1, chan2 }, calculate,
        ChannelBundle { chan3, chan4, chan5 }, executor };

    //Definition ConsoleWriter 1/2/3
    const auto writer1 = [](auto val) { std::cout << "Val1 + Val2: " << val << '\n'; };
    SinkBlock consoleWriter1 { ChannelBundle { chan3 }, writer1, executor };
    const auto writer2 = [](auto val) { std::cout << "Val1 - Val2: " << val << '\n'; };
    SinkBlock consoleWriter2 { ChannelBundle { chan4 }, writer2, executor };
    const auto writer3 = [](auto val) { std::cout << "Val1 * Val2: " << val << "\n\n"; };
    SinkBlock consoleWriter3 { ChannelBundle { chan5 }, writer3, executor };

    //Start generators
    const auto period = 1s;
    const auto offset = 0s;
    const auto cycles = 10;
    numberGenerator1.start(period, offset, cycles);
    numberGenerator2.start(period, offset, cycles);
}
