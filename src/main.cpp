#include <iostream>

#include "Block.h"
#include "Channel.h"

using namespace df;

constexpr int add(int input1, int input2) noexcept { return input1 + input2; }

int main()
{

    //New Block
    Channel<int> channel1;
    Channel<int> channel2;
    Channel<int> channel3;

    Block block1(ChannelBundle(channel1, channel2), add, ChannelBundle(channel3));

    channel1.push(1);
    channel2.push(2);

    if (not channel3.empty()) {
        std::cout << channel3.pop() << '\n';
    };

    return 0;
}
