// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::hash;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

struct Jug;

struct HashPair;

class PairEqual;

bool check_feasible_helper(
    const vector<Jug>& jugs,
    int L,
    int H,
    unordered_set<pair<int, int>, HashPair, PairEqual>* c);

// @include
struct Jug {
  int low, high;
};

class PairEqual {
 public:
  bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
    return a.first == b.first && a.second == b.second;
  }
};

struct HashPair {
  size_t operator()(const pair<int, int>& p) const {
    return hash<int>()(p.first) ^ hash<int>()(p.second);
  }
};

bool check_feasible(const vector<Jug>& jugs, int L, int H) {
  unordered_set<pair<int, int>, HashPair, PairEqual> cache;
  return check_feasible_helper(jugs, L, H, &cache);
}

bool check_feasible_helper(
    const vector<Jug>& jugs,
    int L,
    int H,
    unordered_set<pair<int, int>, HashPair, PairEqual>* c) {
  if (L > H || c->find({L, H}) != c->cend() || (L < 0 && H < 0)) {
    return false;
  }

  // Checks the volume for each jug to see if it is possible.
  for (const Jug& j : jugs) {
    if ((L <= j.low && j.high <= H) ||  // base case: j is contained in [L, H]
        check_feasible_helper(jugs, L - j.low, H - j.high, c)) {
      return true;
    }
  }
  c->emplace(L, H);  // marks this as impossible
  return false;
}
// @exclude

int main(int argc, char* argv[]) {
  int n;
  vector<Jug> jugs;
  jugs.emplace_back(Jug{230, 240});
  jugs.emplace_back(Jug{290, 310});
  jugs.emplace_back(Jug{500, 515});
  assert(check_feasible(jugs, 2100, 2300) == true);
  jugs.clear();
  default_random_engine gen((random_device())());
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 100);
    n = dis(gen);
  }
  for (int i = 0; i < n; ++i) {
    Jug t;
    uniform_int_distribution<int> dis1(0, 999);
    t.low = dis1(gen);
    uniform_int_distribution<int> dis2(t.low + 1, t.low + 20);
    t.high = dis2(gen);
    jugs.emplace_back(t);
  }
  uniform_int_distribution<int> dis1(0, 9999);
  int l = dis1(gen);
  uniform_int_distribution<int> dis2(l + 1, l + 5000);
  int h = dis2(gen);
  cout << boolalpha << check_feasible(jugs, l, h) << endl;
  return 0;
}
