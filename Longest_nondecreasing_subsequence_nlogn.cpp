#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> check_ans(const vector<T> &A) {
  // Empty array
  if (A.empty() == true) {
    return A;
  }

  vector<int> longest_length(A.size(), 1), previous_index(A.size(), -1);
  int max_length_idx = 0;
  for (int i = 1; i < A.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (A[i] >= A[j] && longest_length[j] + 1 > longest_length[i]) {
        longest_length[i] = longest_length[j] + 1;
        previous_index[i] = j;
      }
    }
    // Record the index where longest subsequence ends
    if (longest_length[i] > longest_length[max_length_idx]) {
      max_length_idx = i;
    }
  }

  // Build the longest nondecreasing subsequence
  int max_length = longest_length[max_length_idx];
  vector<T> ret(max_length);
  while (max_length > 0) {
    ret[--max_length] = A[max_length_idx];
    max_length_idx = previous_index[max_length_idx];
  }
  return ret;
}

/*
template <typename T>
int b_search(const vector<T> &tail_values, const T &tar) {
  int l = 0, r = tail_values.size() - 1, ret = -1;

  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (tail_values[m] > tar) {
      r = m - 1;
    } else {
      ret = m, l = m + 1;
    }
  }
  return ret;
}
*/

// @include
template <typename T>
int longest_nondecreasing_subsequence(const vector<T> &A) {
  vector<T> tail_values;
  for (const T &a : A) {
    auto it = upper_bound(tail_values.begin(), tail_values.end(), a);
    if (it == tail_values.end()) {
      tail_values.emplace_back(a);
    } else {
      *it = a;
    }
  }
  return tail_values.size();
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<int> A;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand());
    }
    /*
    for (int i = 0; i < A.size(); ++i) {
      cout << A[i] << ' ';
    }
    cout << endl;
    */
    cout << "n = " << n << endl;
    int ret_length = longest_nondecreasing_subsequence(A);
    vector<int> output = check_ans(A);
    assert(ret_length == output.size());
  }
  return 0;
}
