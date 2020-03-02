/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <dataflow/dataflow.h>
#include <iostream>
#include <utility>

//Simple adder example with writer to stdout.
//
//  DataflowGraph:
//
//                                              ---chan2---> ConsoleWriterEvenNumbers
//  NumberGenerator  --chan1--> SeperateEvenOdd
//                                              ---chan3---> ConsoleWriterOddNumbers
//
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
    auto counter = [count = 0]() mutable { return count++; };
    GeneratorBlock numberGenerator { counter, ChannelBundle { chan1 } };

    //Definition SeperateEvenOdd
    auto transmit = [](auto val1) { return std::tuple { val1, val1 }; };

    auto isEven = [](auto number) { return number % 2 == 0; };
    auto isOdd = [](auto number) { return number % 2 == 1; };

    Block SeperateEvenOdd { ChannelBundle { chan1 }, transmit, ChannelBundle { chan2, chan3 }, executor,
        PredicateBundle { isEven, isOdd } };

    //Definition ConsoleWriterEven/OddNumber
    auto writerEven = [](auto val) { std::cout << "Output even number: " << val << '\n'; };
    SinkBlock consoleWriterEvenNumbers { ChannelBundle { chan2 }, writerEven, executor };

    auto writerOdd = [](auto val) { std::cout << "Output odd number: " << val << '\n'; };
    SinkBlock consoleWriterOddNumbers { ChannelBundle { chan3 }, writerOdd, executor };

    //Start generators
    const auto period = 10ms;
    const auto offset = 0ms;
    const auto cycles = 10;
    numberGenerator.start(period, offset, cycles);
}
