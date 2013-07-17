// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_set>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::hash;
using std::priority_queue;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

// @include
struct Num {
  Num(const int &a, const int &b) : a(a), b(b), val(a + b * sqrt(2)) {}

  const bool operator<(const Num &n) const {
    return val > n.val;
  }

  // Equal function for hash
  const bool operator==(const Num &n) const {
    return a == n.a && b == n.b;
  }

  int a, b;
  double val;
};

// Hash function for Num
class HashNum {
 public:
  const size_t operator()(const Num &n) const {
    return hash<int>()(n.a) ^ hash<int>()(n.b);
  }
};

vector<Num> generate_first_k(const int &k) {
  priority_queue<Num, vector<Num>> min_heap;
  vector<Num> smallest;
  unordered_set<Num, HashNum> hash;

  // Initial for 0 + 0 * sqrt(2)
  min_heap.emplace(0, 0);
  hash.emplace(0, 0);

  while (smallest.size() < k) {
    Num s(min_heap.top());
    smallest.emplace_back(s);
    hash.erase(s);
    min_heap.pop();

    // Add the next two numbers derived from s
    Num c1(s.a + 1, s.b), c2(s.a, s.b + 1);
    if (hash.emplace(c1).second) {
      min_heap.emplace(c1);
    }
    if (hash.emplace(c2).second) {
      min_heap.emplace(c2);
    }
  }
  return smallest;
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int k;
    if (argc == 2) {
      k = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      k = dis(gen);
    }
    vector<Num> ans(generate_first_k(k));
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i].a << ' ' << ans[i].b << ' ' << ans[i].val << endl;
      if (i > 0) {
        assert(ans[i].val >= ans[i - 1].val);
      }
    }
    return 0;
  }
}
