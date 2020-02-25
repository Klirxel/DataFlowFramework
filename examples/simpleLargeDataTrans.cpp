/*
 *          Copyright Schwenk, Kurt <Kurt.Schwenk@gmx.de> 2020
 * Distributed under the Boost Software License, Version 1.0.
 *    (See acompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include <dataflow/dataflow.h>

//Example of tranmission of large data packages.
//
//  DataflowGraph:
//  packageGenerator --chan1--> transmitter --chan2-->  consoleWriter
int main()
{
    //Definition Channels
    using package_type = std::vector<int>;
    const auto max_package_size = 100;
    Channel<package_type> chan1;
    Channel<package_type> chan2;

    //Definiton Executor
    ExecutorSeq executor;

    //Definiton packageGenerator
    const auto init_seed = 324;
    auto rndPackGen = [seed = init_seed]() mutable {
        const auto variable_package_size = std::abs(seed % max_package_size);
        package_type package(variable_package_size);

        std::seed_seq seq { seed };
        seq.generate(package.begin(), package.end());
        seed = package.back();
        return package; //copy ellision
    };

    GeneratorBlock packageGenerator { rndPackGen, ChannelBundle { chan1 } };

    //Definiton Transmitter
    auto transmit = [](auto&& package) {
        return std::forward<decltype(package)>(package);
    };

    Block transmitter { ChannelBundle { chan1 }, transmit,
        ChannelBundle { chan2 }, executor };

    //Definition ConsoleWriter
    const auto writer = [](auto&& package) {
        std::stringstream sstream;
        auto appendToStream = [&sstream](const auto& elem) { sstream << elem << ' '; };
        std::for_each(package.begin(), package.end(), appendToStream);
        std::cout << "\n\nPackage size: " << package.size() << '\n'
                  << "Package data: "
                  << sstream.rdbuf();
    };

    SinkBlock consoleWriter { ChannelBundle { chan2 }, writer, executor };

    //Start generators
    const auto period = 10ms;
    const auto offset = 0ms;
    const auto cycles = 10;
    packageGenerator.start(period, offset, cycles);
}
