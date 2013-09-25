// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "./swap_bits.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

vector<long> precomputed_reverse;

long reverse_x(long x, int n) {
  for (int i = 0, j = n; i < j; ++i, --j) {
    x = swap_bits(x, i, j);
  }
  return x;
}

void create_precomputed_table() {
  for (int i = 0; i < (1 << 16); ++i) {
    precomputed_reverse.emplace_back(reverse_x(i, 15));
  }
}

// @include
long reverse_bits(long x) {
  return precomputed_reverse[(x >> 48) & 0b1111111111111111] |
         precomputed_reverse[(x >> 32) & 0b1111111111111111] << 16 |
         precomputed_reverse[(x >> 16) & 0b1111111111111111] << 32 |
         precomputed_reverse[x & 0b1111111111111111] << 48;
}
// @exclude

int main(int argc, char* argv[]) {
  create_precomputed_table();
  if (argc == 2) {
    long x = atoi(argv[1]);
    cout << "sizeof(x) = " << sizeof(x) << endl;
    cout << "x = " << x << ", reverse x = " << reverse_bits(x) << endl;
    cout << reverse_x(x, 63) << endl;
    assert(reverse_bits(x) == reverse_x(x, 63));
  } else {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
      uniform_int_distribution<long> dis(0, numeric_limits<long>::max());
      long x = dis(gen);
      cout << "x = " << x << ", reverse x = " << reverse_bits(x) << endl;
      assert(reverse_bits(x) == reverse_x(x, 63));
    }
  }
  return 0;
}
