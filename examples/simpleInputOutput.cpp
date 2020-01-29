/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>
#include <dataflow/dataflow.h>

//Simple example with an numberGenerator and an writer to stdout.
//
//  DataflowGraph:
//  NumberGenerator ---channel-----> ConsoleWriter
//
int main()
{
    //Definition Channels
    Channel<int> channel;

    //Definiton Executor
    ExecutorSeq executor;

    //Definiton NumberGenerator
    auto counter = [count = 0]() mutable { return count++; };
    GeneratorBlock numberGenerator { counter, ChannelBundle { channel } };

    //Definition ConsoleWriter
    auto writer = [](int val) { std::cout << "Output: " << val << '\n'; };
    SinkBlock consoleWriter { ChannelBundle { channel }, writer, executor };

    //Start generator
    const auto period = 1s;
    const auto offset = 0s;
    const auto cycles = 10;
    numberGenerator.start(period, offset, cycles);
}
