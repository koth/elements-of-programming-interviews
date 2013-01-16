#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>

using namespace std;

// @include
// Promote to double to prevent precision error
template <typename T>
double find_median(vector<T> &A) {
  int half = A.size() >> 1;
  nth_element(A.begin(), A.begin() + half, A.end());
  if (A.size() & 1) {  // A has odd number elements
    return A[half];
  } else {  // A has even number elements
    T x = A[half];
    nth_element(A.begin(), A.begin() + half - 1, A.end());
    return 0.5 * (x + A[half - 1]);
  }
}

template <typename T>
class Comp {
  private:
    double m;

  public:
    Comp(const double &m) : m(m) {};

    bool operator()(const T &a, const T &b) const {
      return (fabs(a - m) < fabs(b - m));
    }
};

template <typename T>
vector<T> find_k_closest_to_median(vector<T> A, const int &k) {
  double median = find_median(A);

  // Find the element i where |A[i] - median| is k-th smallest
  nth_element(A.begin(), A.begin() + (k - 1), A.end(), Comp<T>(median));

  vector<T> res;
  for (const T &a : A) {
    if (fabs(a - median) < fabs(A[k - 1] - median)) {
      res.emplace_back(a);
    }
  }
  res.resize(k, A[k - 1]);
  return res;
}
// @exclude

template <typename T>
void check_ans(vector<T> &A, const vector<T> &res, const int &k) {
  sort(A.begin(), A.end());
  double median = (A.size() & 1) ? A[A.size() >> 1] : 0.5 * (A[(A.size() >> 1) - 1] + A[A.size() >> 1]);
  vector<double> temp;
  for (const T &a : A) {
    temp.emplace_back(fabs(median - a));
  }
  sort(temp.begin(), temp.end());
  for (const T &r : res) {
    assert(fabs(r - median) <= temp[k - 1]);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 2) {
      n = atoi(argv[1]);
      k = 1 + rand() % n;
    } else if (argc == 3) {
      n = atoi(argv[1]);
      k = atoi(argv[2]);
    } else {
      n = 1 + rand() % 100000;
      k = 1 + rand() % n;
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % (n << 1));
    }
    /*
    for (const int &a : A) {
      cout << a << ' ';
    }
    cout << endl;
    */
    vector<int> res = find_k_closest_to_median(A, k);
    assert(res.size() == k);
    cout << "n = " << n << ", k = " << k << endl;
    /*
    for (const int &a : res) {
      cout << a << ' ';
    }
    cout << endl;
    */
    check_ans(A, res, k);
  }
  return 0;
}
