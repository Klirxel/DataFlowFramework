#include <iostream>

#include "Block.h"

int source1() { return 1; }
int source2() { return 2; }

int filter(int input1, int input2) { return input1 + input2; }

void sink(int input) { std::cout << input << '\n'; }

int main() {

	df::Block<decltype(filter), int, int> filterBlock(filter);

  int channel1 = source1();
  int channel2 = source2();
  int channel3 = filterBlock(channel1, channel2);
  sink(channel3);

  return 0;
}
