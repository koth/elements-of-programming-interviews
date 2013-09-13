// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
template <typename T>
void generate_power_set_helper(const vector<T> &S, int idx, vector<T>* res) {
  if (!res->empty()) {
    // Print the subset.
    copy(res->cbegin(), res->cend() - 1, ostream_iterator<T>(cout, ","));
    cout << res->back();
  }
  cout << endl;

  for (int i = idx; i < S.size(); ++i) {
    res->emplace_back(S[i]);
    generate_power_set_helper(S, i + 1, res);
    res->pop_back();
  }
}

template <typename T>
void generate_power_set(const vector<T> &S) {
  vector<T> res;
  generate_power_set_helper(S, 0, &res);
}
// @exclude

int main(int argc, char *argv[]) {
  vector<int> S;
  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      S.emplace_back(atoi(argv[i]));
    }
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    S.resize(dis(gen));
    for (int i = 0; i < S.size(); ++i) {
      S[i] = i;
    }
  }
  generate_power_set(S);
  return 0;
}
