// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

int find_optimum_subarray_using_comp(const vector<int>& A,
                                     const int& (*comp)(const int&,
                                                        const int&));

// @include
int max_subarray_sum_in_circular(const vector<int>& A) {
  // Find the max in non-circular case and circular case.
  return max(find_optimum_subarray_using_comp(A, max),  // non-circular case.
             accumulate(A.cbegin(), A.cend(), 0) -
                 find_optimum_subarray_using_comp(A, min));  // circular case.
}

int find_optimum_subarray_using_comp(const vector<int>& A,
                                     const int& (*comp)(const int&,
                                                        const int&)) {
  int till = 0, overall = 0;
  for (const int& a : A) {
    till = comp(a, a + till);
    overall = comp(overall, till);
  }
  return overall;
}
// @exclude

// O(n^2) solution
int check_ans(const vector<int>& A) {
  int ans = 0;
  for (int i = 0; i < A.size(); ++i) {
    int sum = 0;
    for (int j = 0; j < A.size(); ++j) {
      sum += A[(i + j) % A.size()];
      ans = max(ans, sum);
    }
  }
  cout << "correct answer = " << ans << endl;
  return ans;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
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
        uniform_int_distribution<int> dis(1, 10000);
        n = dis(gen);
      }
      while (n--) {
        uniform_int_distribution<int> dis(-10000, 10000);
        A.emplace_back(dis(gen));
      }
    }
    int ans = max_subarray_sum_in_circular(A);
    /*
    for (size_t i = 0; i < A.size(); ++i) {
      cout << A[i] << ' ';
    }
    //*/
    cout << endl << "maximum sum = " << ans << endl;
    assert(ans == check_ans(A));
  }
  return 0;
}
