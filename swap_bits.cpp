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

// @include
long swap_bits(long x, int i, int j) {
  if (((x >> i) & 1) != ((x >> j) & 1)) {
    x ^= (1L << i) | (1L << j);
  }
  return x;
}
// @exclude

void simple_test() {
  assert(swap_bits(47, 1, 4) == 61);
  assert(swap_bits(28, 0, 2) == 25);
}

int main(int argc, char *argv[]) {
  simple_test();
  default_random_engine gen((random_device())());
  long x;
  int i, j;
  if (argc == 4) {
    x = atol(argv[1]), i = atoi(argv[2]), j = atoi(argv[3]);
  } else {
    uniform_int_distribution<long> dis(0, numeric_limits<long>::max());
    x = dis(gen);
    uniform_int_distribution<int> digit_dis(0, 63);
    i = digit_dis(gen), j = digit_dis(gen);
  }
  cout << "x = " << x << ", i = " << i << ", j = " << j << endl;
  cout << swap_bits(x, i, j) << endl;
  return 0;
}
