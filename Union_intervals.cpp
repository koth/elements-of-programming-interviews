#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

// @include
template <typename TimeType>
class Interval {
  private:
    class Endpoint {
      public:
        bool isClose;
        TimeType val;
    };

  public:
    Endpoint left, right;

    const bool operator<(const Interval &i) const {
      return left.val != i.left.val ?
             left.val < i.left.val : (left.isClose && !i.left.isClose);
    }
};

template <typename TimeType>
vector<Interval<TimeType> > Union_intervals(vector<Interval<TimeType> > I) {
  // Empty input
  if (I.empty()) {
    return {};
  }

  // Sort intervals according to their left endpoints
  sort(I.begin(), I.end());
  Interval<TimeType> curr(I.front());
  vector<Interval<TimeType> > uni;
  for (int i = 1; i < I.size(); ++i) {
    if (I[i].left.val < curr.right.val ||
        (I[i].left.val == curr.right.val &&
         (I[i].left.isClose || curr.right.isClose))) {
      if (I[i].right.val > curr.right.val ||
          (I[i].right.val == curr.right.val && I[i].right.isClose)) {
        curr.right = I[i].right;
      }
    } else {
      uni.emplace_back(curr);
      curr = I[i];
    }
  }
  uni.emplace_back(curr);
  return uni;
}
// @exclude

template <typename TimeType>
void check_intervals(const vector<Interval<TimeType> > &A) {
  cout << A.size() << endl;
  // only check the intervals do not overlap with each other
  //cout << "0 " << ((A[0].left.isClose) ? '[' : '(') << A[0].left.val << "," << A[0].right.val << ((A[0].right.isClose) ? ']' : ')') << endl;
  for (size_t i = 1; i < A.size(); ++i) {
    //cout << i << ' ' << ((A[i].left.isClose) ? '[' : '(') << A[i].left.val << "," << A[i].right.val << ((A[i].right.isClose) ? ']' : ')') << endl;
    assert(A[i - 1].right.val < A[i].left.val || (A[i - 1].right.val == A[i].left.val && !A[i - 1].right.isClose && !A[i].left.isClose));
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    vector<Interval<int> > A;
    for (int i = 0; i < n; ++i) {
      Interval<int> temp;
      temp.left.isClose = rand() & 1, temp.left.val = rand() % 10000;
      temp.right.isClose = rand() & 1, temp.right.val = 1 + temp.left.val + rand() % 100;
      A.emplace_back(temp);
    }
    vector<Interval<int> > ret = Union_intervals(A);
    if (ret.empty() == false) {
      check_intervals(ret);
    }
  }
  return 0;
}
