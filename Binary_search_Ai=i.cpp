#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cassert>
#include <algorithm>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
int search_index_value_equal(const vector<int> &A) {
  int l = 0, r = A.size() - 1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    int val = A[m] - m;
    if (val == 0) {
      return m;
    } else if (val > 0) {
      r = m - 1;
    } else {  // val < 0
      l = m + 1;
    }
  }
  return -1;
}
// @exclude

// O(n) way to find ans
int check_ans(const vector<int> &A) {
  int ret = -1;
  for (int i = 0; i < A.size(); ++i) {
    if (A[i] == i) {
      return ret;
    }
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<int> A;
    unordered_set<int> table;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (int i = 0; i < n; ++i) {
      int x;
      unordered_set<int>::iterator iter;
      do {
        x = ((rand() & 1) ? -1 : 1) * rand() % 1000;
        iter = table.find(x);
      } while (iter != table.cend());
      table.emplace_hint(iter, x);
      A.emplace_back(x);
    }
    sort(A.begin(), A.end());
    int ans = search_index_value_equal(A);
    if (ans != -1) {
      cout << "A[" << ans << "] = " << A[ans] << endl;
    } else {
      cout << "no entry where A[k] = k" << endl;
    }
    assert(ans = check_ans(A));
  }
  return 0;
}
