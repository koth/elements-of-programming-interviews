#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
template <typename T>
pair<int, int> find_longest_increasing_subarray(const vector<T> &A) {
  int max_len = 1;
  pair<int, int> ans(0, 0);
  int i = 0;
  while (i < A.size()) {
    // Check backwardly and skip if A[j] >= A[j + 1]
    bool is_skippable = false;
    for (int j = i + max_len - 1; j >= i; --j) {
      if (A[j] >= A[j + 1]) {
        i = j + 1;
        is_skippable = true;
        break;
      }
    }

    // Check forwardly if it is not skippable
    if (is_skippable == false) {
      while (i + 1 < A.size() && A[i] < A[i + 1]) {
        ++i, ++max_len;
      }
      ans = {i - max_len + 1, i};
    }
  }
  return ans;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    vector<int> A;
    if (argc > 2) {
      for (size_t i = 1; i < argc; ++i) {
        A.emplace_back(atoi(argv[i]));
      }
    } else {
      int n;
      if (argc == 2) {
        n = atoi(argv[1]);
      } else {
        n = 1 + rand() % 1000000;
      }
      for (int i = 0; i < n; ++i) {
        A.emplace_back((rand() & 1 ? -1 : 1) * rand());
      }
    }
    /*
       for (int i = 0; i < A.size(); ++i) {
       cout << A[i] << ' ';
       }
       cout << endl;
     */
    pair<int, int> result = find_longest_increasing_subarray(A);
    cout << result.first << ' ' << result.second << endl;
    int len = 1;
    for (int i = 1; i < A.size(); ++i) {
      if (A[i] > A[i - 1]) {
        ++len;
      } else {
        len = 1;
      }
      assert(len <= result.second - result.first + 1);
    }
  }
  return 0;
}
