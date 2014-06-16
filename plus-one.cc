// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::stoul;
using std::vector;

// @include
vector<int> plus_one(vector<int> A) {
  ++A.back();
  for (int i = A.size() - 1; i > 0 && A[i] == 10; --i) {
    A[i] = 0, ++A[i - 1];
  }
  if (A[0] == 10) {
    A[0] = 0;
    A.insert(A.begin(), 1, 1);
  }
  return A;
}
// @exclude

vector<int> rand_vector(size_t len) {
  if (!len) {
    return {0};
  }

  default_random_engine gen((random_device())());
  vector<int> A;
  uniform_int_distribution<int> dis_first(1, 9);
  A.emplace_back(dis_first(gen));
  --len;
  while (len) {
    uniform_int_distribution<int> dis(0, 9);
    A.emplace_back(dis(gen));
    --len;
  }
  return A;
}

void small_test() {
  auto res = plus_one({9, 9});
  assert(res.size() == 3 && res[0] == 1 && res[1] == 0 && res[2] == 0);
  res = plus_one({3, 1, 4});
  assert(res.size() == 3 && res[0] == 3 && res[1] == 1 && res[2] == 5);
}

int main(int argc, char** argv) {
  small_test();
  default_random_engine gen((random_device())());
  size_t n;
  if (argc == 2) {
    n = stoul(argv[1]);
  } else {
    uniform_int_distribution<size_t> dis(0, 1000);
    n = dis(gen);
  }
  auto A = rand_vector(n);
  for (int a : A) {
    cout << a;
  }
  cout << endl << endl;
  auto res = plus_one(A);
  for (int a : res) {
    cout << a;
  }
  cout << endl;
  return 0;
}
