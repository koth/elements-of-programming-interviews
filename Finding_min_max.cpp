#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
// Return (min, max) pair of elements in A
template <typename T>
pair<T, T> find_min_max(const vector<T> &A) {
  if (A.size() <= 1) {
    return {A.front(), A.front()};
  }

  // Initialize the min and max pair
  pair<T, T> min_max_pair = minmax(A[0], A[1]);
  for (int i = 2; i + 1 < A.size(); i += 2) {
    pair<T, T> local_pair = minmax(A[i], A[i + 1]);
    min_max_pair = {min(min_max_pair.first, local_pair.first),
                    max(min_max_pair.second, local_pair.second)};
  }
  // Special case: if there is odd number of elements in the array, we still
  // need to compare the last element with the existing answer.
  if (A.size() & 1) {
    min_max_pair = {min(min_max_pair.first, A.back()),
                    max(min_max_pair.second, A.back())};
  }
  return min_max_pair;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand());
    }
    pair<int, int> res = find_min_max(A);
    assert(res.first == *min_element(A.cbegin(), A.cend()) && res.second == *max_element(A.cbegin(), A.cend()));
  }
  return 0;
}
