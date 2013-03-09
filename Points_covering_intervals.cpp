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
    const bool operator()(const Interval<TimeType> &a,
                          const Interval<TimeType> &b) const {
      return a.left != b.left ? a.left < b.left : a.right < b.right;
    }
};

template <typename TimeType>
class RightComp {
  public:
    const bool operator()(const Interval<TimeType> &a,
                          const Interval<TimeType> &b) const {
      return a.right != b.right ? a.right < b.right : a.left < b.left;
    }
};

template <typename TimeType>
vector<TimeType> find_minimum_visits(const vector<Interval<TimeType>> &I) {
  set<Interval<TimeType>, LeftComp<TimeType>> L;
  set<Interval<TimeType>, RightComp<TimeType>> R;
  for (const Interval<TimeType> &i : I) {
    L.emplace(i), R.emplace(i);
  }

  vector<TimeType> S;
  while (L.size() && R.size()) {
    TimeType b = R.cbegin()->right;
    S.emplace_back(R.cbegin()->right);

    // Remove the intervals which intersect with R.cbegin()
    auto it = L.cbegin();
    while (it != L.end() && it->left <= b) {
      R.erase(*it);
      L.erase(it++);
    }
  }
  return S;
}
// @exclude

// O(n^2) checking solution
template <typename TimeType>
void check_ans(const vector<Interval<TimeType>> &I, const vector<TimeType> &ans) {
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

void simple_test(void) {
  vector<Interval<int>> I;
  I.emplace_back(Interval<int>{1, 4});
  I.emplace_back(Interval<int>{2, 8});
  I.emplace_back(Interval<int>{3, 6});
  I.emplace_back(Interval<int>{3, 5});
  I.emplace_back(Interval<int>{7, 10});
  I.emplace_back(Interval<int>{9, 11});
  vector<int> ans = find_minimum_visits(I);
  assert(ans.size() == 2 && ans[0] == 4 && ans[1] == 10);
}

int main(int argc, char *argv[]) {
  simple_test();
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    cout << "Test " << times << endl;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<Interval<int>> A;
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
