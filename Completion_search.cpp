#include <iostream>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>

using namespace std;

// @include
double completion_search(vector<double> &A, const double &budget) {
  sort(A.begin(), A.end());
  // Calculate the prefix sum for A
  vector<double> prefix_sum;
  partial_sum(A.cbegin(), A.cend(), back_inserter(prefix_sum));

  // Find the new upper-bound salary
  for (int i = 0; i < A.size() && budget >= prefix_sum[i]; ++i) {
    double tar = (budget - (i < 1 ? 0 : prefix_sum[i - 1])) / (A.size() - i);
    if ((i - 1 < 0 || A[i - 1] <= tar) && tar <= A[i]) {
      return tar;
    }
  }
  return -1.0;  // no solution
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    vector<double> A;
    double tar;
    if (argc == 2) {
      n = atoi(argv[1]);
      tar = rand();
    } else if (argc == 3) {
      n = atoi(argv[1]), tar = atoi(argv[2]);
    } else {
      n = 1 + rand() % 1000;
      tar = rand() % 100000;
    }
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % 10000);
    }
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    double ret = completion_search(A, tar);
    if (ret != -1) {
      cout << ret << endl;
      double sum = 0.0;
      for (int i = 0; i < n; ++i) {
        if (A[i] > ret) {
          sum += ret;
        } else {
          sum += A[i];
        }
      }
      tar -= sum;
      cout << sum << endl;
      assert(tar < 1.0e-8);
    }
  }
  return 0;
}
