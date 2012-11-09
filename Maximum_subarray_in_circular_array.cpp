#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
// Calculate the non-circular solution
template <typename T>
T find_max_subarray(const vector<T> &A) {
  T maximum_till = 0, maximum = 0;
  for (const T &a : A) {
    maximum_till = max(a, a + maximum_till);
    maximum = max(maximum, maximum_till);
  }
  return maximum;
}

// Calculate the solution which is circular
template <typename T>
T find_circular_max_subarray(const vector<T> &A) {
  // Maximum subarray sum starts at index 0 and ends at or before index i
  vector<T> maximum_begin;
  T sum = A.front();
  maximum_begin.emplace_back(sum);
  for (int i = 1; i < A.size(); ++i) {
    sum += A[i];
    maximum_begin.emplace_back(max(maximum_begin.back(), sum));
  }

  // Maximum subarray sum starts at index i + 1 and ends at the last element
  vector<T> maximum_end(A.size());
  maximum_end.back() = 0;
  sum = 0;
  for (int i = A.size() - 2; i >= 0; --i) {
    sum += A[i + 1];
    maximum_end[i] = max(maximum_end[i + 1], sum);
  }

  // Calculate the maximum subarray which is circular
  T circular_max = 0;
  for (int i = 0; i < A.size(); ++i) {
    circular_max = max(circular_max, maximum_begin[i] + maximum_end[i]);
  }
  return circular_max;
}

template <typename T>
T max_subarray_sum_in_circular(const vector<T> &A) {
  return max(find_max_subarray(A), find_circular_max_subarray(A));
}
// @exclude

// O(n^2) solution
template <typename T>
T check_ans(const vector<T> &A) {
  T ans = 0;
  for (int i = 0; i < A.size(); ++i) {
    T sum = 0;
    for (int j = 0; j < A.size(); ++j) {
      sum += A[(i + j) % A.size()];
      ans = max(ans, sum);
    }
  }
  cout << "correct answer = " << ans << endl;
  return ans;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<int> A;
    if (argc > 2) {
      for (int i = 1; i < argc; ++i) {
        A.emplace_back(atoi(argv[i]));
      }
    } else {
      if (argc == 2) {
        n = atoi(argv[1]);
      } else {
        n = 1 + rand() % 10000;
      }
      while (n--) {
        A.emplace_back(((rand() & 1) ? -1 : 1) * rand() % 10000);
      }
    }
    int ans = max_subarray_sum_in_circular(A);
    /*
    for (size_t i = 0; i < A.size(); ++i) {
      cout << A[i] << ' ';
    }
    */
    cout << endl << "maximum sum = " << ans << endl;
    assert(ans == check_ans(A));
  }
  return 0;
}
