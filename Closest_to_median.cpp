// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::nth_element;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

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
 public:
  Comp(const double &m) : m_(m) {};

  const bool operator()(const T &a, const T &b) const {
    return fabs(a - m_) < fabs(b - m_);
  }

 private:
  double m_;
};

template <typename T>
vector<T> find_k_closest_to_median(vector<T> A, const int &k) {
  // Find the element i where |A[i] - median| is k-th smallest
  nth_element(A.begin(), A.begin() + k - 1, A.end(), Comp<T>{find_median(A)});
  return {A.cbegin(), A.cbegin() + k};
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

void simple_test(void) {
  vector<int> D = {3,2,3,5,7,3,1};
  vector<int> Dexpres = {2,3,3};
  vector<int> Dres = find_k_closest_to_median(D,3);
  check_ans(D, Dres, 3);
  for (const int &d : Dres) {
    cout << d << ' ';
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 2) {
      n = atoi(argv[1]);
      uniform_int_distribution<int> k_dis(1, n);
      k = k_dis(gen);
    } else if (argc == 3) {
      n = atoi(argv[1]);
      k = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> n_dis(1, 100000);
      n = n_dis(gen);
      uniform_int_distribution<int> k_dis(1, n);
      k = k_dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> dis(0, (n << 1) - 1);
    for (int i = 0; i < n; ++i) {
      A.emplace_back(dis(gen));
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
