#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>

using namespace std;

// @include
template <typename T>
int search_first(const vector<T> &A, const T &k) {
  int l = 0, r = A.size() - 1, res = -1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (A[m] > k) {
      r = m - 1;
    } else if (A[m] == k) {
      // Record the solution and keep searching the left part
      res = m, r = m - 1;
    } else {  // A[m] < k
      l = m + 1;
    }
  }
  return res;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++ times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 100000;
    }
    vector<int> A;
    int k = rand() % n;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % n);
    }
    sort(A.begin(), A.end());
    int ans = search_first(A, k);
    cout << "k = " << k << " locates at " << ans << endl;
    if (ans != -1) {
      cout << "A[k] = " << A[ans] << endl;
    }
    auto it = find(A.cbegin(), A.cend(), k);
    assert((it == A.cend() && ans == -1) || (distance(A.cbegin(), it) == ans));
  }
  return 0;
}
