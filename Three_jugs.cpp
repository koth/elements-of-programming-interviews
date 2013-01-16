#include <iostream>
#include <cassert>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
class Jug {
  public:
    int low, high;
};

class PairEqual {
  public:
    const bool operator()(const pair<int, int> &a,
                          const pair<int, int> &b) const {
      return a.first == b.first && a.second == b.second;
    }
};

class HashPair {
  public:
    const size_t operator()(const pair<int, int> &p) const {
      return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

bool check_feasible_helper(const vector<Jug> &jugs, const int &L,
                           const int &H, unordered_set<pair<int, int>, 
                                                       HashPair,
                                                       PairEqual> &c) {
  if (L > H || c.find({L, H}) != c.cend() || (L < 0 && H < 0)) {
    return false;
  }

  // Check the volume for each jug to see if it is possible
  for (const Jug &j : jugs) {
    if ((L <= j.low && j.high <= H) ||  // base case: j is contained in [L, H]
      check_feasible_helper(jugs, L - j.low, H - j.high, c)) {
      return true;
    }
  }
  c.emplace(L, H);  // marks this as impossible
  return false;
}

bool check_feasible(const vector<Jug> &jugs, const int &L, const int &H) {
  unordered_set<pair<int, int>, HashPair, PairEqual> cache;
  return check_feasible_helper(jugs, L, H, cache);
}
// @exclude

int main(int argc, char *argv[]) {
  int n;
  vector<Jug> jugs;
  jugs.emplace_back(Jug{230, 240});
  jugs.emplace_back(Jug{290, 310});
  jugs.emplace_back(Jug{500, 515});
  assert(check_feasible(jugs, 2100, 2300) == true);
  jugs.clear();
  srand(time(nullptr));
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100;
  }
  for (int i = 0; i < n; ++i) {
    Jug t;
    t.low = rand() % 1000;
    t.high = t.low + 1 + rand() % 20;
    jugs.emplace_back(t);
  }
  int l = rand() % 10000;
  int h = l + 1 + rand() % 5000;
  cout << boolalpha << check_feasible(jugs, l, h) << endl;
  return 0;
}
