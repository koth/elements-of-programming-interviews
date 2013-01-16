#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename TimeType>
class Interval {
  public:
    TimeType left, right;
};

template <typename TimeType>
class LeftComp {
  public:
    bool operator()(const Interval<TimeType> &a,
                    const Interval<TimeType> &b) const {
      return a.left != b.left ? a.left < b.left : a.right < b.right;
    }
};

template <typename TimeType>
class RightComp {
  public:
    bool operator()(const Interval<TimeType> &a,
                    const Interval<TimeType> &b) const {
      return a.right != b.right ? a.right < b.right : a.left < b.left;
    }
};

template <typename TimeType>
vector<TimeType> find_minimum_visits(const vector<Interval<TimeType> > &I) {
  set<Interval<TimeType>, LeftComp<TimeType> > L;
  set<Interval<TimeType>, RightComp<TimeType> > R;
  for (const Interval<TimeType> &i : I) {
    L.emplace(i), R.emplace(i);
  }

  vector<TimeType> S;
  while (L.size() && R.size()) {
    S.emplace_back(R.cbegin()->right);

    // Remove the intervals which intersect with R.cbegin()
    auto l_end = L.upper_bound(*R.cbegin()), it = L.cbegin();
    while (it != l_end) {
      R.erase(*it);
      L.erase(it++);
    }
  }
  return S;
}
// @exclude

// O(n^2) checking solution
template <typename TimeType>
void check_ans(const vector<Interval<TimeType> > &I, const vector<TimeType> &ans) {
  vector<bool> is_visited(I.size(), false);
  for (const TimeType &a : ans) {
    for (int i = 0; i < I.size(); ++i) {
      if (a >= I[i].left && a <= I[i].right) {
        is_visited[i] = true;
      }
    }
  }

  for (const bool &b : is_visited) {
    assert(b == true);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<Interval<int> > A;
    for (int i = 0; i < n; ++i) {
      int left = rand() % 10000;
      int right = 1 + left + rand() % 100;
      A.emplace_back(Interval<int>{left, right});
    }
    vector<int> ans(find_minimum_visits(A));
    check_ans(A, ans);
  }
  return 0;
}
