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
    int a, b;
    double val;

    Num(const int &a, const int &b) : a(a), b(b), val(a + b * sqrt(2)) {}

    const bool operator<(const Num &n) const {
      return val > n.val;
    }

    // Equal function for hash
    const bool operator==(const Num &n) const {
      return a == n.a && b == n.b;
    }
};

// Hash function for Num
class HashNum {
  public:
    const size_t operator()(const Num &n) const {
      return hash<int>()(n.a) ^ hash<int>()(n.b);
    }
};

vector<Num> generate_first_k(const int &k) {
  priority_queue<Num, vector<Num> > min_heap;
  vector<Num> smallest;
  unordered_set<Num, HashNum> hash;

  // Initial for 0 + 0 * sqrt(2)
  min_heap.emplace(Num(0, 0));
  hash.emplace(Num(0, 0));

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
      cout << ans[i].a << ' ' << ans[i].b << ' ' << ans[i].val << endl;
      if (i > 0) {
        assert(ans[i].val >= ans[i - 1].val);
      }
    }
    return 0;
  }
}
