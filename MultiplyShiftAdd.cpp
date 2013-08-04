// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

// @include
unsigned add_no_operator(unsigned a, unsigned b) {
  unsigned sum = 0, carryin = 0, k = 1;
  while (k) {
    unsigned ak = a & k, bk = b & k;
    unsigned carryout =  (ak & bk) | (ak & carryin) | (bk & carryin);
    sum |= (ak ^ bk ^ carryin);
    carryin = carryout << 1;
    k <<= 1;
  }
  return sum;
}

unsigned multiply_no_operator(unsigned x, unsigned y) {
  unsigned sum = 0, k = 1, scaled_y = y;
  while (k) {
    // Examine the k-th bit of x
    if (x & k) {
      sum = add_no_operator(sum, scaled_y);
    }
    k <<= 1;
    scaled_y <<= 1;
  }
  return sum;
}
// @exclude

int main(int argc, char *argv[]) {
  if (argc == 3) {
    unsigned int x = atoi(argv[1]), y = atoi(argv[2]);
    unsigned int res = add_no_operator(x, y);
    cout << "x = " << x << ", y = " << y << ", res = " << res << endl;
    assert(res == x + y);
  } else {
    default_random_engine gen((random_device())());
    // random test, only works if the product not greater than 2^32 - 1
    for (int i = 0; i < 100000; ++i) {
      uniform_int_distribution<int> dis(0, 65534);
      unsigned int x = dis(gen), y = dis(gen);
      unsigned int prod = multiply_no_operator(x, y);
      assert(prod == x * y);
      cout << "PASS: x = " << x << ", y = " << y << "; prod = " << prod << endl;
    }
  }
  return 0;
}
