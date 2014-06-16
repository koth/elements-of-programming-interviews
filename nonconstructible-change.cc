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
using std::ostream_iterator;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

// @include
int nonconstructible_change(vector<int> A) {
  sort(A.begin(), A.end());
  int sum = 0;
  for (int a : A) {
    if (a > sum + 1) {
      break;
    }
    sum += a;
  }
  return sum + 1;
}
// @exclude

void small_test() {
  vector<int> A = {1, 2, 3, 4};
  assert(11 == nonconstructible_change(A));
  A = {1, 2, 2, 4};
  assert(10 == nonconstructible_change(A));
  A = {2, 3, 4, 5};
  assert(1 == nonconstructible_change(A));
  A = {1, 3, 2, 1};
  assert(8 == nonconstructible_change(A));
  A = {1, 3, 2, 5};
  assert(12 == nonconstructible_change(A));
  A = {1, 3, 2, 6};
  assert(13 == nonconstructible_change(A));
  A = {1, 3, 2, 7};
  assert(14 == nonconstructible_change(A));
  A = {1, 3, 2, 8};
  assert(7 == nonconstructible_change(A));
}

int main(int argc, char* argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 1000);
    n = dis(gen);
  }
  uniform_int_distribution<int> dis(1, 1000);
  vector<int> A;
  generate_n(back_inserter(A), n, [&] { return dis(gen); });
  copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  int ans = nonconstructible_change(A);
  cout << ans << endl;
  return 0;
}
