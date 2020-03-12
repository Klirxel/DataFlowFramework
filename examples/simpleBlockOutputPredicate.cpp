/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>
#include <utility>

#include <dataflow/dataflow.h>
using namespace dataflow;


//Simple block output predicate example.
//
//  DataflowGraph:
//
//                                                  ---chan_even---> ConsoleWriterEvenNumbers
//  NumberGenerator  --chan_num--> EvenOddSeperator
//                                                  ---chan_odd----> ConsoleWriterOddNumbers
//
//  Description:
//  With an output predicate of an block
//  it can be controlled if output from an kernel
//  of an block should be written to an output channel.
//
int main()
{
    //Definition Channels
    Channel<int> chan_num;
    Channel<int> chan_even;
    Channel<int> chan_odd;

    //Definiton Executor
    ExecutorSeq executor;

    //Definiton NumberGenerator1
    auto counter = [count = 0]() mutable { return count++; };
    GeneratorBlock numberGenerator { counter, ChannelBundle { chan_num } };

    //Definition SeperateEvenOdd
    auto doubler = [](auto number) { return std::tuple { number, number }; };

    auto isEven = [](auto number) { return number % 2 == 0; };
    auto isOdd = [](auto number) { return number % 2 == 1; };

    Block EvenOddSeperator { ChannelBundle { chan_num }, doubler,
      ChannelBundle { chan_even, chan_odd }, executor,
      OutputPredicate{isEven, isOdd} };

    //Definition ConsoleWriterEven/OddNumber
    auto writerEven = [](auto val) { std::cout << "Output even number: " << val << '\n'; };
    SinkBlock consoleWriterEvenNumbers { ChannelBundle { chan_even }, writerEven, executor };

    auto writerOdd = [](auto val) { std::cout << "Output odd number: " << val << '\n'; };
    SinkBlock consoleWriterOddNumbers { ChannelBundle { chan_odd }, writerOdd, executor };

    //Start generators
    const auto period = 10ms;
    const auto offset = 0ms;
    const auto cycles = 10;
    numberGenerator.start(period, offset, cycles);
}
