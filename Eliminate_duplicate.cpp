#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// @include
template <typename T>
void eliminate_duplicate(vector<T> &A) {
  sort(A.begin(), A.end());  // makes identical elements become neighbors
  // unique() removes adjacent duplicates and returns an iterator to the 
  // element the follows the last element not removed. The effect of resize()
  // is to restrict A to the distinct element.
  A.resize(distance(A.begin(), unique(A.begin(), A.end())));
}
// @exclude

template <typename T>
void check_ans(const vector<T> &A) {
  for (int i = 1; i < A.size(); ++i) {
    assert(A[i] != A[i - 1]);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<int> A;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = rand() % 100000;
    }
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % n);
    }
    eliminate_duplicate(A);
    check_ans(A);
  }
  return 0;
}
