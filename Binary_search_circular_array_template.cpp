#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>
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
template <typename T>
int search_smallest(const vector<T> &A) {
  int l = 0, r = A.size() - 1;
  while (l < r) {
    int m = l + ((r - l) >> 1);
    if (A[m] > A[r]) {
      l = m + 1;
    } else {  // A[m] <= A[r]
      r = m;
    }
  }
  return l;
}
// @exclude

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
    unordered_set<int> table;
    for (size_t i = 0; i < n; ++i) {
      while (true) {
        int x = rand();
        if (table.emplace(x).second) {
          A.emplace_back(x);
          break;
        }
      }
    }
    sort(A.begin(), A.end());
    int shift = rand() % n;
    reverse(A.begin(), A.end());
    reverse(A.begin(), A.begin() + shift + 1);
    reverse(A.begin() + shift + 1, A.end());
    /*
       for (size_t i = 0; i < n; ++i) {
       cout << A[i] << ' ';
       }
       cout << endl;
     */
    assert((shift + 1) % n == search_smallest(A));
  }
  // hand-made tests
  vector<int> A;
  A.emplace_back(2);
  A.emplace_back(3);
  A.emplace_back(4);
  assert(0 == search_smallest(A));
  A.clear();
  A.emplace_back(100);
  A.emplace_back(101);
  A.emplace_back(102);
  A.emplace_back(2);
  A.emplace_back(5);
  assert(3 == search_smallest(A));
  A.clear();
  A.emplace_back(10);
  A.emplace_back(20);
  A.emplace_back(30);
  A.emplace_back(40);
  A.emplace_back(5);
  assert(4 == search_smallest(A));
  return 0;
}
