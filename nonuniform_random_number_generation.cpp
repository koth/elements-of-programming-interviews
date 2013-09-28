// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::distance;
using std::endl;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

// @include
double nonuniform_random_number_generation(const vector<double>& T,
                                           const vector<double>& P) {
  vector<double> prefix_P;
  prefix_P.emplace_back(0);
  partial_sum(P.cbegin(), P.cend(), back_inserter(prefix_P));
  // gen object is used to generate random numbers.
  default_random_engine gen((random_device())());
  // Generate a random number in [0.0, 1.0].
  uniform_real_distribution<double> dis(0.0, 1.0);
  // upper_bound returns an iterator pointing to the first element in
  // (prefix_P.cbegin(),prefix_P.cend()) which compares greater than dis(gen)
  // which is a uniform random number in [0.0,1.0].
  auto it = upper_bound(prefix_P.cbegin(), prefix_P.cend(), dis(gen));
  return T[distance(prefix_P.cbegin(), it) - 1];
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  size_t n;
  if (argc == 2) {
    n = static_cast<size_t>(atoi(argv[1]));
  } else {
    uniform_int_distribution<size_t> dis(1, 100);
    n = dis(gen);
  }
  vector<double> T(n);
  iota(T.begin(), T.end(), 0);
  vector<double> P;
  double full_prob = 1.0;
  for (int i = 0; i < n - 1; ++i) {
    uniform_real_distribution<double> dis(0.0, full_prob);
    double pi = dis(gen);
    P.emplace_back(pi);
    full_prob -= pi;
  }
  P.emplace_back(full_prob);
  for (int i = 0; i < T.size(); ++i) {
    cout << T[i] << ' ';
  }
  cout << endl;
  for (int i = 0; i < P.size(); ++i) {
    cout << P[i] << ' ';
  }
  cout << endl;
  cout << nonuniform_random_number_generation(T, P) << endl;
  return 0;
}
