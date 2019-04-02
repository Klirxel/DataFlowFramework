#include <iostream>
#include "Block.h"

int source1() { return 1; }
int source2() { return 2; }

int filter(int input1, int input2) { return input1 + input2; }
int addOne(int input) { return input + 1; }
void sink(int input) { std::cout << input << '\n'; }

int main() {

//New Block
  df::Channel<int> channel1;
  df::Channel<int> channel2;
  df::Channel<int> channel3;
  df::Channel<int> channel4;

  df::Block block1(channel1, addOne, channel2);
  df::Block block2(channel2, addOne, channel3);
  df::Block block3(channel3, addOne, channel4);

  channel1.push(0);
  
  if(not channel4.empty()){
	  std::cout << channel4.pop() << '\n';
  };

  return 0;
}
