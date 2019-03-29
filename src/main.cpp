#include <iostream>

int source() { return 0; }

int filter(int input) { return input; }

void sink(int input) { std::cout << input << '\n'; }

int main() {

  int channel1, channel2;
  channel1 = source();
  channel2 = filter(channel1);
  sink(channel2);

  return 0;
}
