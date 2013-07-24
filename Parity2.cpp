// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <random>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;

short parity1(unsigned long x) {
  short result = 0;
  while (x) {
    result ^= (x & 1);
    x >>= 1;
  }
  return result;
}

// @include
short parity2(unsigned long x) {
  short result = 0;
  while (x) {
    result ^= 1;
    x &= (x - 1);  // drops the lowest set bit of x
  }
  return result;
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  if (argc == 2) {
    long int x = atol(argv[1]);
    assert(parity1(x) == parity2(x));
    cout << "x = " << x << ", parity = " << parity2(x) << endl;
  } else {
    for (int times = 0; times < 1000; ++times) {
      uniform_int_distribution<int> dis(0, numeric_limits<int>::max());
      long int x = dis(gen);
      assert(parity1(x) == parity2(x));
      cout << "x = " << x << ", parity = " << parity2(x) << endl;
    }
  }
  return 0;
}
