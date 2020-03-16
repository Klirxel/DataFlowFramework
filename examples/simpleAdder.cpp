/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>

#include <dataflow/dataflow.h>
using namespace dataflow;

//Simple adder example with writer to stdout.
//
//  DataflowGraph:
//  NumberGenerator1 --chan1--> |
//                              | Adder --chan3--> ConsoleWriter
//  NumberGenerator2 --chan2--> |
//
int main()
{
    //Definition Channels
    Channel<int> chan1;
    Channel<int> chan2;
    Channel<int> chan3;

    //Definiton Executor
    ExecutorSeq executor;

    //Definiton NumberGenerator1
    auto counter1 = [count = 0]() mutable { return count++; };
    GeneratorBlock numberGenerator1 { counter1, ChannelBundle { chan1 } };

    //Definiton NumberGenerator2
    auto counter2 = [count = 0]() mutable { return count++; };
    GeneratorBlock numberGenerator2 { counter2, ChannelBundle { chan2 } };

    //Definition Adder
    auto add = [](auto val1, auto val2) { return val1 + val2; };
    Block adder { ChannelBundle { chan1, chan2 }, add, ChannelBundle { chan3 }, executor };

    //Definition ConsoleWriter
    auto writer = [](auto val) { std::cout << "Output: " << val << '\n'; };
    SinkBlock consoleWriter { ChannelBundle { chan3 }, writer, executor };

    //Start generators
    const auto period = 10ms;
    const auto offset = 0ms;
    const auto cycles = 10;
    numberGenerator1.start(period, offset, cycles);
    numberGenerator2.start(period, offset, cycles);
}
