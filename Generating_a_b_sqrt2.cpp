#include <iostream>
#include <cassert>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
class Num {
  public:
    int a_, b_;
    double val_;

    Num(const int &a, const int &b) : a_(a), b_(b), val_(a + b * sqrt(2)) {}

    const bool operator<(const Num &n) const {
      return val_ > n.val_;
    }

    // Equal function for hash
    const bool operator==(const Num &n) const {
      return a_ == n.a_ && b_ == n.b_;
    }
};

// Hash function for Num
class HashNum {
  public:
    const size_t operator()(const Num &n) const {
      return hash<int>()(n.a_) ^ hash<int>()(n.b_);
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
    Num c1(s.a_ + 1, s.b_), c2(s.a_, s.b_ + 1);
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
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int k;
    if (argc == 2) {
      k = atoi(argv[1]);
    } else {
      k = 1 + rand() % 10000;
    }
    vector<Num> ans(generate_first_k(k));
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i].a_ << ' ' << ans[i].b_ << ' ' << ans[i].val_ << endl;
      if (i > 0) {
        assert(ans[i].val_ >= ans[i - 1].val_);
      }
    }
    return 0;
  }
}
