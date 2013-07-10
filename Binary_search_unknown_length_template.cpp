#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// @include
template <typename T>
int binary_search_unknown_len(const vector<T> &A, const T &k) {
  // Find the possible range where k exists
  int p = 0;
  while (true) {
    try {
      T val = A.at((1 << p) - 1);
      if (val == k) {
        return (1 << p) - 1;
      } else if (val > k) {
        break;
      }
    }
    catch (exception& e) {
      break;
    }
    ++p;
  }

  // Binary search between indices 2^(p - 1) and 2^p - 2
  int l = 1 << (p - 1), r = (1 << p) - 2;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    try {
      T val = A.at(m);
      if (val == k) {
        return m;
      } else if (val > k) {
        r = m - 1;
      } else {  // A[m] < k
        l = m + 1;
      }
    }
    catch (exception& e) {
      r = m - 1;  // search the left part if out of boundary
    }
  }
  return -1;  // nothing matched k
}
// @exclude

void small_test(void) {
  vector<int> A = {1, 2, 3};
  assert(binary_search_unknown_len(A, 3) == 2);
  assert(binary_search_unknown_len(A, 1) == 0);
  assert(binary_search_unknown_len(A, 2) == 1);
  assert(binary_search_unknown_len(A, 4) == -1);
}

int main(int argc, char *argv[]) {
  small_test();
  int n, k;
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    if (argc == 2) {
      n = atoi(argv[1]);
      k = rand();
    } else if (argc == 3) {
      n = atoi(argv[1]);
      k = atoi(argv[2]);
    } else {
      n = 1 + rand() % 1000000;
      k = rand() % (n << 1);
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % (n << 1));
    }
    sort(A.begin(), A.end());
    cout << n << ' ' << k << endl;
    int idx = binary_search_unknown_len(A, k);
    cout << idx << endl;
    assert((idx == -1 && binary_search(A.cbegin(), A.cend(), k) == false) || A[idx] == k);
  }
  return 0;
}
