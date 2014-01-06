// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
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
using std::queue;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

// @include
struct Num {
  Num(int a, int b) : a(a), b(b), val(a + b * sqrt(2)) {}

  // Equal function for hash.
  bool operator==(const Num& n) const { return a == n.a && b == n.b; }

  int a, b;
  double val;
};

struct CompareNum {
  bool operator()(Num const& a, Num const& b) { return a.val > b.val; }
};

// Hash function for Num.
struct HashNum {
  size_t operator()(const Num& n) const {
    return hash<int>()(n.a) ^ hash<int>()(n.b);
  }
};

vector<Num> generate_first_k(int k) {
  priority_queue<Num, vector<Num>, CompareNum> min_heap;
  vector<Num> smallest;
  unordered_set<Num, HashNum> hash;

  // Initial for 0 + 0 * sqrt(2).
  min_heap.emplace(0, 0);
  hash.emplace(0, 0);

  while (smallest.size() < k) {
    Num s(min_heap.top());
    smallest.emplace_back(s);
    hash.erase(s);
    min_heap.pop();

    // Add the next two numbers derived from s.
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

vector<Num> golden(int k) {
  vector<Num> smallest;
  smallest.emplace_back(0, 0);
  queue<Num> q1, q2;
  q1.emplace(1, 0);
  q2.emplace(0, 1);
  for (int i = 1; i < k; ++i) {
    auto q1_f = q1.front(), q2_f = q2.front();
    if (q1_f.val < q2_f.val) {
      smallest.emplace_back(q1_f);
      q1.pop();
      q1.emplace(q1_f.a + 1, q1_f.b);
      q2.emplace(q1_f.a, q1_f.b + 1);
    } else {
      smallest.emplace_back(q2_f);
      q2.pop();
      q2.emplace(q2_f.a, q2_f.b + 1);
    }
  }
  return smallest;
}

int main(int argc, char* argv[]) {
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
    for (size_t i = 0; i < ans.size(); ++i) {
      cout << ans[i].a << ' ' << ans[i].b << ' ' << ans[i].val << endl;
      if (i > 0) {
        assert(ans[i].val >= ans[i - 1].val);
      }
    }
    auto gold_res = golden(k);
    for (size_t i = 0; i < k; ++i) {
      assert(ans[i] == gold_res[i]);
      //cout << "first " << ans[i].a << " " << ans[i].b << " " << ans[i].val << endl;
      //cout << "second " << gold_res[i].a << " " << gold_res[i].b << " " << gold_res[i].val << endl;
    }
  }
  return 0;
}
