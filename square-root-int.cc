// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;

// @include
int square_root(int x) {
  if (x <= 1) {
    return x;
  }

  long left = 0, right = x;
  while (left + 1 < right) {
    long mid = left + ((right - left) >> 1);
    long square_m = mid * mid;
    if (square_m == x) {
      return mid;
    } else if (square_m < x) {
      left = mid;
    } else {  // square_m > x
      right = mid - 1;
    }
  }
  if (right * right <= x) {
    return right;
  }
  return left;
}
// @exclude

int main(int argc, char** argv) {
  int x;
  if (argc == 2) {
    x = stoi(argv[1]);
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(0, numeric_limits<int>::max());
    for (int times = 0; times < 100000; ++times) {
      x = dis(gen);
      int res[2];
      cout << "x is " << x << endl;
      cout << (res[0] = square_root(x)) << ' ' << (res[1] = static_cast<int>(sqrt(x))) << endl;
      assert(res[0] == res[1]);
    }
  }
  x = 2147395599;
  cout << square_root(x) << endl;
  return 0;
}
