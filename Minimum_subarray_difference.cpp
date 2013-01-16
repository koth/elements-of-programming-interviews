#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>
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
int minimize_difference(const vector<int> &A) {
  int sum = accumulate(A.cbegin(), A.cend(), 0);

  unordered_set<int> is_Ok;
  is_Ok.emplace(0);
  for (const int &item : A) {
    for (int v = sum >> 1; v >= item; --v) {
      if (is_Ok.find(v - item) != is_Ok.cend()) {
        is_Ok.emplace(v);
      }
    }
  }

  // Find the first i from middle where is_Ok[i] == true
  for (int i = sum >> 1; i > 0; --i) {
    if (is_Ok.find(i) != is_Ok.cend()) {
      return (sum - i) - i;
    }
  }
  return sum;   // one thief takes all
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  vector<int> A;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else if (argc == 1) {
    n = 1 + rand() % 50;
  } else {
    for (int i = 1; i < argc; ++i) {
      A.emplace_back(atoi(argv[i]));
    }
    n = 0;
  }
  for (size_t i = 0; i < n; ++i) {
    A.emplace_back(rand() % 100);
    cout << A[i] << ' ';
  }
  cout << endl;
  int sum = accumulate(A.cbegin(), A.cend(), 0);
  cout << sum << endl;
  cout << "minimum difference = " << minimize_difference(A) << endl;
  return 0;
}
