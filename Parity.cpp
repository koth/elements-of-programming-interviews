// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <random>

#include "./Parity1.h"
#include "./Parity2.h"
#include "./Parity3.h"
#include "./Parity4.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;

int main(int argc, char* argv[]) {
  build_table();
  if (argc == 2) {
    long x = atol(argv[1]);
    assert(parity1(x) == parity3(x));
    assert(parity2(x) == parity3(x));
    assert(parity3(x) == parity4(x));
    cout << "x = " << x << ", parity = " << parity3(x) << endl;
  } else {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
      uniform_int_distribution<long> dis(0, numeric_limits<long>::max());
      long x = dis(gen);
      assert(parity1(x) == parity3(x));
      assert(parity2(x) == parity3(x));
      assert(parity4(x) == parity3(x));
      cout << "x = " << x << ", parity = " << parity3(x) << endl;
    }
  }
  return 0;
}
