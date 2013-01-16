#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
T find_optimum_subarray_using_comp(const vector<T> &A, 
                                   const T&(*comp)(const T&, const T&)) {
  T till = 0, overall = 0;
  for (const T &a : A) {
    till = comp(a, a + till);
    overall = comp(overall, till);
  }
  return overall;
}

template <typename T>
T max_subarray_sum_in_circular(const vector<T> &A) {
  // Find the max in non-circular case and circular case
  return max(find_optimum_subarray_using_comp(A, max),  // non-circular case
             accumulate(A.cbegin(), A.cend(), 0) -
             find_optimum_subarray_using_comp(A, min));  // circular case
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
    //*/
    cout << endl << "maximum sum = " << ans << endl;
    assert(ans == check_ans(A));
  }
  return 0;
}
