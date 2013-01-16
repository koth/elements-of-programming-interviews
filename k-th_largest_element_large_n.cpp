#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <algorithm>

using namespace std;

// @include
template <typename T>
T find_k_th_largest_unknown_length(istringstream &sin, const int &k) {
  vector<T> M;
  T x;
  while (sin >> x) {
    M.emplace_back(x);
    if (M.size() == (k << 1) - 1) {
      // Keep the k largest elements and discard the small ones
      nth_element(M.begin(), M.begin() + k - 1, M.end(), greater<T>());
      M.resize(k);
    }
  }
  nth_element(M.begin(), M.begin() + k - 1, M.end(), greater<T>());
  return M[k - 1];  // return the k-th largest one
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 2) {
      n = atoi(argv[1]);
      k = 1 + rand() % n;
    } else if (argc == 3) {
      n = atoi(argv[1]), k = atoi(argv[2]);
    } else {
      n = 1 + rand() % 100000;
      k = 1 + rand() % n;
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % 10000000);
    }
    stringstream ss;
    for (const int &a : A) {
      ss << a << ' ';
    }
    /*
    cout << "n = " << n << ", k = " << k << endl;
    cout << ss.str() << endl;
    //*/
    istringstream sin(ss.str());
    int res = find_k_th_largest_unknown_length<int>(sin, k);
    nth_element(A.begin(), A.begin() + A.size() - k, A.end());
    cout << res << endl << A[A.size() - k] << endl;
    assert(res == A[A.size() - k]);
  }
  return 0;
}
