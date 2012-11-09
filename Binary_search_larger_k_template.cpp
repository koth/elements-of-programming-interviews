#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cassert>

using namespace std;

// @include
template <typename T>
int search_first_larger_k(const vector<T> &A, const T &k) {
  int l = 0, r = A.size() - 1, res = -1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (A[m] > k) {
      // Record the solution and keep searching the left part
      res = m, r = m - 1;
    } else {  // A[m] <= k
      l = m + 1;
    }
  }
  return res;
}
// @exclude

template <typename T>
int check_ans(vector<T> &A, const T &k) {
  for (int i = 0; i < A.size(); ++i) {
    if (A[i] > k) {
      return i;
    }
  }
  return -1;
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
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % n);
    }
    sort(A.begin(), A.end());
    int k = rand() % n;
    int ans = search_first_larger_k(A, k);
    cout << "k = " << k << " locates at " << ans << endl;
    if (ans != -1) {
      cout << "A[k] = " << A[ans] << endl;
    }
    assert(ans == check_ans(A, k));
  }
  return 0;
}
