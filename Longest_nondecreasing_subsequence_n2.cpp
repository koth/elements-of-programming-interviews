#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>

using namespace std;

// @include
template <typename T>
vector<T> longest_nondecreasing_subsequence(const vector<T> &A) {
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
// @exclude

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

template <typename T>
int check_ans(const vector<T> &A) {
  // Empty array
  if (A.empty() == true) {
    return 0;
  }

  vector<T> tail_values;
  tail_values.emplace_back(A[0]);
  for (int i = 1; i < A.size(); ++i) {
    int tar_idx = b_search(tail_values, A[i]);
    if (tar_idx == tail_values.size() - 1) {
      tail_values.emplace_back(A[i]);
    } else if (tail_values[tar_idx + 1] > A[i]) {
      tail_values[tar_idx + 1] = A[i];
    }
  }
  return tail_values.size();
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<int> A;
    if (argc == 2) {
      n = atoi(argv[1]);
      for (int i = 0; i < n; ++i) {
        A.emplace_back(rand());
      }
    } else if (argc == 1) {
      n = 1 + rand() % 10000;
      for (int i = 0; i < n; ++i) {
        A.emplace_back(rand());
      }
    } else {
      for (int i = 1; i < argc; ++i) {
        A.emplace_back(atoi(argv[i]));
      }
    }
    /*
    for (int i = 0; i < A.size(); ++i) {
      cout << A[i] << ' ';
    }
    cout << endl;
    */
    vector<int> output = longest_nondecreasing_subsequence(A);
    for (int i = 1; i < output.size(); ++i) {
      assert(output[i - 1] <= output[i]);
    }
    cout << "n = " << n << endl;
    assert(output.size() == check_ans(A));
    /*
    for (int i = 0; i < output.size(); ++i) {
      cout << output[i] << ' ';
    }
    cout << endl;
    */
  }
  return 0;
}
